//
// Created by yttcy on 2022/4/9.
//

#ifndef MYWEBSERVER_EVENTHANDER_H
#define MYWEBSERVER_EVENTHANDER_H
#include <cstdlib>
#include <functional>
#include <sys/epoll.h>
#include <memory>

class Http;

//回调函数
typedef std::function<void()> CallBack;

class Reactor;


class EventHander{
private:
    int fd_;
    Reactor *reactor_;

    u_int32_t events_;
    u_int32_t revents_;
    u_int32_t lastevents_; //我不知道维持这个变量有什么用???先留着看吧。

    //持有Http对象
    std::weak_ptr<Http> holder_;

    //四个回调函数
    CallBack connhandle_;
    CallBack readhandle_;
    CallBack errorhandle_;
    CallBack writehandle_;

public:
    EventHander(Reactor *reactor,int fd);
    EventHander(Reactor *reactor);
    void setHolder(std::shared_ptr<Http> holder);
    std::shared_ptr<Http> getHolder();
    int getFd();
    void setEvents(u_int32_t events);
    void setRevents(u_int32_t events);
    u_int32_t& getEvents();
    void setConnHandle(CallBack function);
    void setReadHandle(CallBack function);
    void setWriteHandle(CallBack function);
    void setErrorHandle(CallBack function);
    void handleEvent();
    bool equalAndUpdateLastEvents();
    uint32_t getLastEvents();
};

typedef std::shared_ptr<EventHander> sp_EventHander;

#endif //MYWEBSERVER_EVENTHANDER_H
