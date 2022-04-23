//
// Created by yttcy on 2022/4/9.
//

#include "../ServerHeadfiles/EventHander.h"


EventHander::EventHander(Reactor *reactor1,int fd):
fd_(fd),
reactor_(reactor1)
{


}

EventHander::EventHander(Reactor *reactor1):
reactor_(reactor1)
{

}


void EventHander::setHolder(std::shared_ptr<Http> holder) {
    holder_ = holder;

}

std::shared_ptr<Http> EventHander:: getHolder(){
    std::shared_ptr<Http> ret(holder_.lock());
    return ret;
}

int EventHander::getFd() {
    return fd_;
}

void EventHander::setEvents(u_int32_t events) {
    events_ = events;
}

//这里为什么要返回引用呢
u_int32_t& EventHander::getEvents() {
    return events_;
}

void EventHander::setRevents(u_int32_t events) {
    revents_ = events;
}

void EventHander::setConnHandle(CallBack function) {
    connhandle_ = function;
}

void EventHander::setReadHandle(CallBack function) {
    readhandle_ = function;
}

void EventHander::setWriteHandle(CallBack function) {
    writehandle_ = function;
}

void EventHander::setErrorHandle(CallBack function) {
    errorhandle_ = function;
}

void EventHander::handleEvent() {
    events_ = 0;
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        events_ = 0;
        return;
    }
    if (revents_ & EPOLLERR) {
        if (errorhandle_) errorhandle_();
        events_ = 0;
        return;
    }
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
        readhandle_();
    }
    if (revents_ & EPOLLOUT) {
        writehandle_();
    }
    //也就是说当连接到了，每次都设置状态
    connhandle_();
}

bool EventHander::equalAndUpdateLastEvents() {
    bool ret = (events_ == lastevents_);
    lastevents_ = events_;
    return ret;
}

uint32_t EventHander::getLastEvents() {
    return lastevents_;
}
