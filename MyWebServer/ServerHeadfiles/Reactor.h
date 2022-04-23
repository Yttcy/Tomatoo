//
// Created by yttcy on 2022/4/9.
//

#ifndef MYWEBSERVER_REACTOR_H
#define MYWEBSERVER_REACTOR_H
#include <functional>
#include <vector>
#include <memory>
#include <cassert>
#include "../ThreadHeadfiles/CurrentThread.h"
#include "EventHander.h"
#include <sys/eventfd.h>
#include <unistd.h>
#include "../ThreadHeadfiles/CountDownLatch.h"

class Epoll;

class Reactor{
    typedef std::function<void()> Functor;
private:
    bool looping_; //标志是否在循环中
    bool quit_; //标志是否该退出
    bool eventhanding_; //标志是否在处理事件
    int wakeupfd_; // 当子线程来了事件，通知主线程epoll_wait结束来执行functors_
    mutable MutexLock lock_;
    std::shared_ptr<Epoll> epoll_;
    std::vector<Functor> functors_; //函数指针的方法
    bool calling_unsolved_func_; //为解决的方法
    const pid_t thread_id_; //当前线程的id
    std::shared_ptr<EventHander> wakeup_eventhander_; //就是当子线程来了事件之后，主线程epoll_wait返回。
public:
    Reactor();
    ~Reactor();
    void addtoEpoll(sp_EventHander eventHander,int timeout);
    void delfromEpoll(sp_EventHander eventHander);
    void updateEpoll(sp_EventHander eventHander,int timeout);
    void queue(Functor &&cb);
    void runInLoop(Functor &&cb);
    void dispatch();
    void quit();
    void assertInBaseThread();

private:
    void wakeup();
    void handRead();
    void handConn();
    void doFunctors();
};



#endif //MYWEBSERVER_REACTOR_H
