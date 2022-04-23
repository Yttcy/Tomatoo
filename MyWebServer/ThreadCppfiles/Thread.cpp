//
// Created by yttcy on 2022/4/11.
//
#include "../ThreadHeadfiles/Thread.h"
#include "../ThreadHeadfiles/CurrentThread.h"

namespace CurrentThread {
    __thread int t_cachedTid = 0;
    __thread char t_tidString[32];
    __thread int t_tidStringLength = 6;
    __thread const char* t_threadName = "default";
}

pid_t gettid() { return static_cast<pid_t>(::syscall(SYS_gettid)); }

void CurrentThread::cacheTid() {
    if (t_cachedTid == 0) {
        t_cachedTid = gettid();
        t_tidStringLength =
                snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
    }
}

// 为了在线程中保留name,tid这些数据
struct ThreadData {
    ThreadFunction func_;
    std::string name_;
    pid_t* tid_;
    CountDownLatch* latch_;

    ThreadData(const ThreadFunction& func, const std::string& name, pid_t* tid,
               CountDownLatch* latch)
            : func_(func), name_(name), tid_(tid), latch_(latch) {}

    void runInThread() {
        *tid_ = CurrentThread::tid();
        tid_ = NULL;
        latch_->countDown();
        latch_ = NULL;

        CurrentThread::t_threadName = name_.empty() ? "Thread" : name_.c_str();
        prctl(PR_SET_NAME, CurrentThread::t_threadName);

        func_();
        CurrentThread::t_threadName = "finished";
    }
};



Thread::Thread(const ThreadFunction &function,const std::string &name):
start_(false),
join_(false),
pthreadid_(0),
pid_(0),
threadFunction_(function),
name_(name),
lock_(1)
{
    setDefaultName();
}

void Thread::setDefaultName() {
    if(name_.empty()){
        name_ = "Thread";
    }
}

Thread::~Thread(){
    if (start_ && !join_) pthread_detach(pthreadid_);
}

void* startThread(void *obj){
    ThreadData *data = (ThreadData *)obj;
    data->runInThread();
    delete data;
    return nullptr;
}

void Thread::start(){
    assert(!start_);
    start_ = true;
    ThreadData *data = new ThreadData(threadFunction_,name_,&pid_,&lock_);
    if(pthread_create(&pthreadid_, nullptr, startThread,data)){
        printf("create thread failed\n");
        start_ = false;
        delete data;
    }else{
        //也就是这里要等到ThreadData开始运行的时候才行。?
        //要是子线程先进行通知操作，这个条件变量还没有开始wait会是什么结果，
        //没什么问题，这个wait函数外面封装了，判断count的值，没什么问题
        lock_.wait();
        assert(pid_ > 0);
    }
}

int  Thread::join() {
    assert(start_);
    assert(!join_);
    join_ = true;
    return pthread_join(pthreadid_, nullptr);
}

/*
 * bool start_;
    bool join_;
    pthread_t pthreadid_;
    pid_t pid_;
    ThreadFunction threadFunction_;
    std::string name_;
    //这里还要加上锁，参考的是陈硕大佬的那本《muduo》
    CountDownLatch lock_;
 */