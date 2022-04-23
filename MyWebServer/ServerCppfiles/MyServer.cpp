//
// Created by yttcy on 2022/4/9.
//

#include "../ServerHeadfiles/MyServer.h"
#include "../util/Util.h"

MyServer::MyServer(Reactor *reactor, int threadnum, int port):
reactor_(reactor),
threadnum_(threadnum),
port_(port),
listenfd_(socket_bind_listen(port_)),
eventHanders_(new EventHander(reactor,listenfd_)),
threadpool_(new ReactorThreadPool(reactor_,threadnum_))
{


    if(listenfd_ < 0){
        printf("yes error\n");
        exit(-1);
    }
    //主线程只是来处理连接的，有没有必要设置为非阻塞的呢。
    //遵循规范，onelooponethread，IO复用和非阻塞，该设置为非阻塞的。
    setnonblocking(listenfd_);
}

void MyServer::start(){
    //设置的是边缘触发，每次要处理完所有的请求。
    threadpool_->start();
    eventHanders_->setEvents(EPOLLIN|EPOLLET); //这里报错，这个eventHanders_好像没有初始化
    eventHanders_->setConnHandle(std::bind(&MyServer::handleThisConn,this));
    eventHanders_->setReadHandle(std::bind(&MyServer::handleNewConn,this));

    //开启了start没有走到这里，难道是死锁了，不应该啊
    reactor_->addtoEpoll(eventHanders_,0);
    //服务开始了，已经添加到epoll中去了，就是还没有epoll_wait
    start_ = true;
}

//先测试一个版本，当来到连接的时候，先输出客户端的地址信息。
void MyServer::handleNewConn() {
    assert(start_);
    struct sockaddr_in client_addr{};
    socklen_t client_addr_lengtht = sizeof(client_addr);
    //这个监听套接字是非阻塞的，不会阻塞在这里
    int clientfd;
    //下面这个客户端端口号是客户端随机分配的。服务器只要记住就可以了。
    //现在问题来了，为什么只能连接一个
    while((clientfd = accept(listenfd_,(struct sockaddr *)&client_addr,&client_addr_lengtht)) > 0){
        printf("new connect form address : %s throuth port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        printf("clientfd is %d\n",clientfd);

        Reactor *next_reactor = threadpool_->getNextReactor();
        if(clientfd > MAXFDS){
            close(clientfd);
            continue;
        }

        if(setnonblocking(clientfd) < 0){
            printf("set nonblocking failed!!\n");
            return;
        }

        closeNagleAlgh(clientfd);

        //注意这里的对象会被析构了，所以test的方法就没有用了，反正了就是很恶心
//        std::shared_ptr<test> tt(new test(clientfd,next_reactor));
//        next_reactor->queue(std::bind(&test::newEvent,tt));

//        auto tt = new test(clientfd,next_reactor);
//        next_reactor->queue([tt] { tt->newEvent(); });

        std::shared_ptr<Http> http(new Http(next_reactor,clientfd));
        http->getEventHander()->setHolder(http);
        next_reactor->queue([http]{http->newEvent();});


        //为什么这个马上就调用析构函数了呢
    }
    //这里如果不设置那么就会出现问题，第二个连接没办法进来。
    //因为handleThisConn修改的是描述符的，所以我们要主动修改事件的属性。有点恶心
    //因为epoll返回的时候是根据事件的属性来确定的，不是fd的属性。要同步啊，哥们。
    eventHanders_->setEvents(EPOLLIN | EPOLLET);
}

void MyServer::handleThisConn() {
    //注意这里是修改fd描述符的属性，不是事件的属性
    reactor_->updateEpoll(eventHanders_,0);
}