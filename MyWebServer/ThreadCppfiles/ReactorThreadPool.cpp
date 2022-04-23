//
// Created by yttcy on 2022/4/13.
//

#include "../ThreadHeadfiles/ReactorThreadPool.h"

ReactorThreadPool::ReactorThreadPool(Reactor *base_reactor,int thread_num):
thread_num_(thread_num),
base_reactor_(base_reactor),
next_(0),
started_(false)
{

}

void ReactorThreadPool::start() {
    //验证还没有进行start操作，如果start两次，那就很糟糕。
    base_reactor_->assertInBaseThread();
    started_ = true;

    for(int i=0;i<thread_num_;++i){
        std::shared_ptr<ReactorThread> t(new ReactorThread());
        threads_.push_back(t);

        loops_.emplace_back(t->startDispatch());
    }
}

//确认线程池已经启动了
Reactor* ReactorThreadPool::getNextReactor() {
    base_reactor_->assertInBaseThread();
    assert(started_);
    //如果线程池全部关闭了，就给主线程来处理。
    Reactor *reactor = base_reactor_;
    if(!loops_.empty()){
        reactor = loops_[next_];
        next_ = (next_+1)%thread_num_;
    }
    return reactor;
}
