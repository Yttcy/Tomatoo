//
// Created by yttcy on 2022/4/9.
//
#include "../ServerHeadfiles/Epoll.h"


Epoll::Epoll():
epollfd_(epoll_create1(EPOLL_CLOEXEC)),
events_(EVNET_MAXNUM)
{

}

void Epoll::epoll_add(sp_EventHander hander,int timeout){
    int fd = hander->getFd();

    //补上
    if(timeout > 0){
        add_timer(hander,timeout);
        fdhttps_[fd] = hander->getHolder();
    }
//    printf("be added fd is : %d\n",fd);
    struct epoll_event event;
    event.data.fd = fd;
    event.events = hander->getEvents();
    hander->equalAndUpdateLastEvents();

    fdevents_[fd] = hander;
    if(epoll_ctl(epollfd_,EPOLL_CTL_ADD,fd,&event) < 0){
        printf("epoll add error\n");
        fdevents_[fd].reset();
    }


}
void Epoll::epoll_del(sp_EventHander hander){
    int fd = hander->getFd();
    struct epoll_event event;
    event.data.fd = fd;
    event.events = hander->getLastEvents();

    if(epoll_ctl(epollfd_,EPOLL_CTL_DEL,fd,&event) < 0){
        printf("epoll del error\n");
    }
    fdevents_[fd].reset();
    fdhttps_[fd].reset();
    //同时这里http处理也要reset();没问题
}


//这个只是修改对应的描述符的属性，
//eventhander_还是要自己修改，
void Epoll::epoll_mod(sp_EventHander hander,int timeout){
    if(timeout > 0){
        add_timer(hander, timeout);
    }
    int fd = hander->getFd();
    //这里是如果不相等才会进入这里吗，
    if (!hander->equalAndUpdateLastEvents()) {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = hander->getEvents();
        if (epoll_ctl(epollfd_, EPOLL_CTL_MOD, fd, &event) < 0) {

            printf("epoll_mod error\n");
            fdevents_[fd].reset();
        }
    }
}

void Epoll::add_timer(sp_EventHander hander, int timeout) {
    std::shared_ptr<Http> t = hander->getHolder();
    if(t){
        timeManager_.addTime(t,timeout);
    }else{
        printf("add time failed\n");
    }
}

//你为什么不设置返回值呢，真的是离谱啊
std::vector<sp_EventHander> Epoll::poll(){
    while(true){
        size_t EPOLL_WAITTIME = timeManager_.getMinTime();
        int event_count = epoll_wait(epollfd_,&*events_.begin(),events_.size(),EPOLL_WAITTIME);
        if(event_count < 0){
            printf("errno is %d \n",errno);
            printf("epoll_wait error\n");
            exit(1);
        }
        //这是得到对应的事件处理器，
        std::vector<sp_EventHander> ret = getEventsRequest(event_count);
        return ret;
    }
}

std::vector<sp_EventHander> Epoll::getEventsRequest(int events_num) {
    std::vector<sp_EventHander> req_data;
    for (int i = 0; i < events_num; ++i) {
        // 获取有事件产生的描述符
        int fd = events_[i].data.fd;

        sp_EventHander cur_req = fdevents_[fd];

        if (cur_req) {
            cur_req->setRevents(events_[i].events);
            cur_req->setEvents(0);
            // 加入线程池之前将Timer和request分离
            // cur_req->seperateTimer();
            req_data.push_back(cur_req);
        } else {
            printf("error int getEventsrequest\n");
        }
    }
    return req_data;
}

void Epoll::handleExpired() {
    timeManager_.handleExpiredEvents();
}