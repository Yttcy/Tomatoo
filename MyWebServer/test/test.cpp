//
// Created by yttcy on 2022/4/14.
//

#include "test.h"

test::test(int clientfd,Reactor *reactor):
clientfd_(clientfd),
reactor_(reactor),
eventHander_(new EventHander(reactor_,clientfd_))
{
    eventHander_->setEvents(EPOLLIN | EPOLLET);
    eventHander_->setReadHandle(std::bind(&test::readtelnet,this));
    eventHander_->setConnHandle(std::bind(&test::conntelnet,this));
}

void test::readtelnet(){
    std::string dst;
    //我曹，为什么这里的描述符为0，我真的是服了，心态崩了。难道是对象被析构了吗?不可能啊
    //还真是被析构了，Eventhander没有保存这个，Http的时候要保存啊。
    readn(clientfd_,dst);
    printf("%s",dst.c_str());
    eventHander_->setEvents(EPOLLIN | EPOLLET);
}

void test::conntelnet(){
    reactor_->updateEpoll(eventHander_,0);
}

void test::newEvent() {
    reactor_->addtoEpoll(eventHander_,0);
}


