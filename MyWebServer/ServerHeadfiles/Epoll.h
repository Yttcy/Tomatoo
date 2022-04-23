//
// Created by yttcy on 2022/4/9.
//

#ifndef MYWEBSERVER_EPOLL_H
#define MYWEBSERVER_EPOLL_H
#include <vector>
#include <sys/epoll.h>
#include <memory>
#include "EventHander.h"
#include "../ThreadHeadfiles/CurrentThread.h"
#include "Time.h"


typedef std::shared_ptr<EventHander> sp_EventHander;

//定义超时时间是不是太长了，感觉应该用优先队列的最小值来作为这个超时时间。
//#define EPOLL_WAITTIME 100000
#define EVNET_MAXNUM 2048

class Epoll{
private:
    static const int MAXFDS = 10000;
    int epollfd_;
    std::vector<epoll_event> events_;
    std::shared_ptr<EventHander> fdevents_[MAXFDS];
    std::shared_ptr<Http> fdhttps_[MAXFDS];
    TimeManager timeManager_;
    //这里要加上一个和eventhander对应的HTTP数据处理类。
    //这里加上一个定时操作，不着急先处理，最后在加入定时器操作。


public:
    Epoll();
    void epoll_add(sp_EventHander hander,int timeout); //epoll 添加被轮询的事件
    void epoll_del(sp_EventHander hander); //删除 描述符
    void epoll_mod(sp_EventHander hander,int timeout); //修改状态
    void add_timer(sp_EventHander hander,int timeout);
    std::vector<sp_EventHander> poll();
    std::vector<sp_EventHander> getEventsRequest(int events_num);
    //这就是处理超时的http连接。
    void handleExpired();
};

#endif //MYWEBSERVER_EPOLL_H
