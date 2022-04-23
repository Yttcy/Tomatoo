//
// Created by yttcy on 2022/4/14.
//

#ifndef MYWEBSERVER_TEST_H
#define MYWEBSERVER_TEST_H

#include "../ServerHeadfiles/EventHander.h"
#include "../ServerHeadfiles/Reactor.h"

//写一个echo的测试类。

typedef std::function<void()> function;

class test {
private:
    int clientfd_;
    Reactor *reactor_;
    std::shared_ptr<EventHander> eventHander_;
public:
    test(int clientfd,Reactor *reactor);
    void readtelnet();
    void conntelnet();
    void newEvent();
};


#endif //MYWEBSERVER_TEST_H
