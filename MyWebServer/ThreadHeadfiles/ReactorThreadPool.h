//
// Created by yttcy on 2022/4/13.
//

#ifndef MYWEBSERVER_REACTORTHREADPOOL_H
#define MYWEBSERVER_REACTORTHREADPOOL_H

#include "ReactorThread.h"

class ReactorThreadPool:public noncopyable{
private:
    Reactor *base_reactor_;
    int thread_num_;
    bool started_;
    int next_;
    std::vector<std::shared_ptr<ReactorThread>> threads_;
    std::vector<Reactor*> loops_;
public:
    explicit ReactorThreadPool(Reactor *base_reactor,int thread_num);
    Reactor* getNextReactor();
    void start();
};



#endif //MYWEBSERVER_REACTORTHREADPOOL_H
