//
// Created by yttcy on 2022/4/13.
//

#ifndef MYWEBSERVER_REACTORTHREAD_H
#define MYWEBSERVER_REACTORTHREAD_H

#include "../ServerHeadfiles/Reactor.h"
#include "Condition.h"
#include "Thread.h"

typedef std::function<void()> function;
class ReactorThread:public noncopyable{
private:
    Reactor *reactor_;
    bool exiting_;
    Thread thread_;
    MutexLock lock_;
    Condition cond_;
public:

    ReactorThread();
    ~ReactorThread();
    Reactor* startDispatch();

private:

    void threadFunc();

};




#endif //MYWEBSERVER_REACTORTHREAD_H
