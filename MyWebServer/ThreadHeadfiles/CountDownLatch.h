    //
// Created by yttcy on 2022/4/11.
//

#ifndef MYWEBSERVER_COUNTDOWNLATCH_H
#define MYWEBSERVER_COUNTDOWNLATCH_H

#include "MutexLock.h"
#include "Condition.h"


class CountDownLatch:public noncopyable{
private:
    MutexLock lock_;
    Condition cond_;
    int count_;
public:
    explicit CountDownLatch(int count):count_(count),lock_(),cond_(lock_){

    }
    void wait(){
        MutexLockGuard lock_G(lock_);
        while(count_ > 0){
            //这一步是原子操作，也就是会自动的解锁并等待通知，
            //当wait执行完了之后就会自动的给锁加上，
            //至于为什么要用循环，因为某些事件也可能唤醒这个，比如说信号。
            cond_.wait();
        }
    }
    void countDown(){
        MutexLockGuard lock_G(lock_);
        --count_;
        if(count_ == 0) cond_.notifyAll();
    }
};




#endif //MYWEBSERVER_COUNTDOWNLATCH_H
