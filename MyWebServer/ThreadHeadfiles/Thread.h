//
// Created by yttcy on 2022/4/11.
//

#ifndef MYWEBSERVER_THREAD_H
#define MYWEBSERVER_THREAD_H

#include "../util/Util.h"
#include <pthread.h>
#include <functional>
#include <sys/syscall.h>
#include <sys/prctl.h>
#include "CountDownLatch.h"

typedef std::function<void()> ThreadFunction;
class Thread:public noncopyable{
private:
    bool start_;
    bool join_;
    pthread_t pthreadid_;
    pid_t pid_;
    ThreadFunction threadFunction_;
    std::string name_;
    //这里还要加上锁，参考的是陈硕大佬的那本《muduo》
    CountDownLatch lock_;

public:
    explicit Thread(const ThreadFunction &function,const std::string &name=std::string());
    ~Thread();
    void start();
    int join();
    bool started(){return start_== true;}
    pid_t getPid(){return pid_;}
    std::string getName(){return name_;}
private:
    void setDefaultName();
};




#endif //MYWEBSERVER_THREAD_H
