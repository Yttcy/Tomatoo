//
// Created by yttcy on 2022/4/9.
//

#ifndef MYWEBSERVER_MYSERVER_H
#define MYWEBSERVER_MYSERVER_H

#include <memory>
#include "EventHander.h"
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <functional>
#include "Reactor.h"
#include "../ThreadHeadfiles/ReactorThreadPool.h"
#include "../test/test.h"
#include "Http.h"


class MyServer{
private:
    int port_;  //这个服务器的端口号
    int listenfd_; //服务器的监听套接字
    bool start_; //服务器是否开启
    Reactor *reactor_; //服务器的Reactor实例
    int threadnum_; //开启的线程数
    static const int MAXFDS = 10000; //最大一万个连接
    std::shared_ptr<EventHander> eventHanders_;
    std::unique_ptr<ReactorThreadPool> threadpool_;                    //这儿还差一个线程池子

public:
    MyServer(Reactor *reactor,int threadnum,int port);
    void handleNewConn();
    void handleThisConn();
    void start();
};



#endif //MYWEBSERVER_MYSERVER_H
