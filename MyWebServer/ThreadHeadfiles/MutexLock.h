//
// Created by yttcy on 2022/4/11.
//

#ifndef MYWEBSERVER_MUTEXLOCK_H
#define MYWEBSERVER_MUTEXLOCK_H


#include "../util/Util.h"
#include "CurrentThread.h"
#include <pthread.h>
#include <cassert>



/*
 * 就是如果一个线程锁住了，抢占到了锁，那么这个想成的holder_
 * 变量就不为0，
 * lock的时候设置当前的线程id，
 * 析构的时候呢就是重新将holder_变量设置为0
 * 巧妙的设计啊。
 *
 * 按照陈硕大佬的说法，就是互斥器加上条件变量，可以完成所有同步
 *
 *
 * */

class MutexLock:public noncopyable{
private:
    friend class Condition;
    pthread_mutex_t mutex_; //互斥锁
    pid_t holder_;//用这个来标识线程id,当没有锁住的时候就是0

public:
    MutexLock(): holder_(0){
        pthread_mutex_init(&mutex_, nullptr);

    }
    ~MutexLock(){
        assert(holder_==0);
        pthread_mutex_destroy(&mutex_);
    }
    bool isLockedByThisThread(){
        return holder_ == CurrentThread::tid();
    }
    void assertLocked(){
        assert(isLockedByThisThread());
    }
    void lock(){
        pthread_mutex_lock(&mutex_);
        holder_ = CurrentThread::tid();
    }
    void unlock(){
        holder_ = 0;
        pthread_mutex_unlock(&mutex_);
    }
    //只能给Condition调用，用户代码不能调用这个函数。
    pthread_mutex_t* getPthreadMutex(){
        return &mutex_;
    }
};

class MutexLockGuard:public noncopyable{
private:
    MutexLock &lock_;
public:
    //禁止隐式转换
    explicit MutexLockGuard(MutexLock& mutexLock):lock_(mutexLock){
        lock_.lock();
    }
    ~MutexLockGuard(){
        lock_.unlock();
    }
};

#define MutexLockGuard(x) static_assert(false,"missing mutex guard var name")


#endif //MYWEBSERVER_MUTEXLOCK_H
