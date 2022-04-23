//
// Created by yttcy on 2022/4/11.
//

#ifndef MYWEBSERVER_CONDITION_H
#define MYWEBSERVER_CONDITION_H

#include "MutexLock.h"

class Condition:public noncopyable{
private:
    MutexLock &lock_;
    pthread_cond_t pcond_;
public:
    explicit Condition(MutexLock &mutexLock):lock_(mutexLock){
        pthread_cond_init(&pcond_, nullptr);
    }
    ~Condition(){
        pthread_cond_destroy(&pcond_);
    }
    void wait(){
        pthread_cond_wait(&pcond_,lock_.getPthreadMutex());
    }
    void notify(){
        pthread_cond_signal(&pcond_);
    }
    void notifyAll(){
        pthread_cond_broadcast(&pcond_);
    }
};





#endif //MYWEBSERVER_CONDITION_H
