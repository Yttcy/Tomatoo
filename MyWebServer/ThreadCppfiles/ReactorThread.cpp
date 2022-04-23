//
// Created by yttcy on 2022/4/13.
//

#include "../ThreadHeadfiles/ReactorThread.h"

ReactorThread::ReactorThread():
reactor_(nullptr),
lock_(),
cond_(lock_),
exiting_(false),
thread_(std::bind(&ReactorThread::threadFunc,this),"ReactorThread")
{

}

ReactorThread::~ReactorThread() {
    exiting_ = true;
    if(reactor_ != nullptr){
        thread_.join();
        reactor_->quit();
    }
}

Reactor* ReactorThread::startDispatch() {
    assert(!thread_.started());
    thread_.start();
    //条件变量一直等到线程调用threadFunc方法，这个方法会初始化reactor变量
    // 然后reactor就可以开始分发任务了啊
    {
        MutexLockGuard lockGuard(lock_);
        while(reactor_ == nullptr){
            cond_.wait();
        }
    }
    return reactor_;
}

//这个是要传给线程的方法，线程的runInThread最终会调用这个方法。
void ReactorThread::threadFunc() {

    Reactor reactor;
    {
        MutexLockGuard lockGuard(lock_);
        reactor_ = &reactor;
        cond_.notify();
    }
    reactor.dispatch();
    reactor_ = nullptr;
}