//
// Created by yttcy on 2022/4/9.
//

#include <csignal>
#include "../ServerHeadfiles/Reactor.h"
#include "../ServerHeadfiles/Epoll.h"

//创造一个事件描述符，用于之间线程的通信
//问题是每个线程得到的eventfd的文件描述符的值不是一样的。
int getEventFd(){
    int event_fd = eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
//    printf("thread %d get the eventfd--%d\n",CurrentThread::tid(),event_fd);
    if(event_fd < 0){
        //后面在这里写进日志文件中
        return -1;
    }
    return event_fd;
}

Reactor::Reactor():
quit_(false),
looping_(false),
wakeupfd_(getEventFd()),
epoll_(new Epoll()),
eventhanding_(false),
calling_unsolved_func_(false),
thread_id_(CurrentThread::tid()),//???这里后面要来搞这个线程id
wakeup_eventhander_(new EventHander(this,wakeupfd_)) //到这里this构造好了吗???
{
    //要屏蔽这个SIGPIPE信号，不然sendfile的时候对端关闭就终止进程了
    signal(SIGPIPE,SIG_IGN);
    wakeup_eventhander_->setEvents(EPOLLIN|EPOLLET);
    wakeup_eventhander_->setReadHandle([this] { handRead(); });
    wakeup_eventhander_->setConnHandle([this] { handConn(); });
    epoll_->epoll_add(wakeup_eventhander_,0);
}

Reactor::~Reactor() {
    close(wakeupfd_);
}

void Reactor::queue(Functor &&cb) {

    {
        MutexLockGuard lock(lock_);
        functors_.emplace_back(std::move(cb));
    }
    //这里总感觉有点奇怪，调用这个函数的时候，thread_id_ 肯定总是等于CurrentThread::tid()的啊
    //除非在调用这个方法的时候中途被抢占了。
    //对啊，当前是主线程，但是在修改子线程
    if(thread_id_ != CurrentThread::tid() || calling_unsolved_func_){
        //这里应该是主线程，但是在调用子线程的方法，修改子线程的变量，唤醒子线程
        wakeup();
    }
}

void Reactor::runInLoop(Functor &&cb) {
    if(thread_id_ == CurrentThread::tid()){
        cb();
    }else{
        queue(std::move(cb));
    }
}


void Reactor::addtoEpoll(sp_EventHander eventHander,int timeout) {
    epoll_->epoll_add(eventHander,timeout);
}

void Reactor::delfromEpoll(sp_EventHander eventHander) {
    epoll_->epoll_del(eventHander);
}

void Reactor::updateEpoll(sp_EventHander eventHander,int timeout) {
    epoll_->epoll_mod(eventHander,timeout);
}

void Reactor::dispatch(){
    assert(!looping_);
    looping_ = true;
    quit_ = false;
    std::vector<sp_EventHander> rets;
    while(!quit_){
        rets.clear();
        rets = epoll_->poll();
        eventhanding_ = true;
        for(auto &ret:rets){
            ret->handleEvent();
        }
        eventhanding_ = false;
        doFunctors();
        epoll_->handleExpired();
    }
}

void Reactor::assertInBaseThread() {
    assert(thread_id_ == CurrentThread::tid());
}

void Reactor::quit(){
    quit_ = true;
    //???这儿还要写是不是在此次线程中。
}


//下面是私有的方法。
void Reactor::handRead() {
    int64_t one;
    ssize_t readnum = readn(wakeupfd_,&one,sizeof(one));
    if(readnum != sizeof(one)){
        printf("readn wakeupfd error\n");
    }
    wakeup_eventhander_->setEvents(EPOLLIN|EPOLLET);
}

void Reactor::handConn() {
    updateEpoll(wakeup_eventhander_,0);
}

//为什么要wakeup，通知所有的线程。
void Reactor::wakeup() {
    uint64_t one;
//    printf("wakeupfd_ is %d\n",wakeupfd_);
    int num = writen(wakeupfd_,(char*)&one,sizeof(one));
    if(num != sizeof(one)){
        printf("writen wakeupfd error\n");
    }
}

void Reactor::doFunctors() {
    std::vector<Functor> fun_vec;
    calling_unsolved_func_ = true;
    //这里是交换出来，减小临界区，可以让线程更充分的运行。
    {
        MutexLockGuard lockGuard(lock_);
        fun_vec.swap(functors_);
    }
    for(int i=0;i<fun_vec.size();++i){
        fun_vec[i]();
    }
    calling_unsolved_func_ = false;
}