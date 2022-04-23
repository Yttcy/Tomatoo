//
// Created by yttcy on 2022/4/16.
//

#ifndef MYWEBSERVER_TIME_H
#define MYWEBSERVER_TIME_H
#include <memory>
#include <queue>
#include <sys/time.h>
#include "Http.h"

class Http;

class TimeNode{
private:
    bool deleted_;
    size_t expiredtime_;
    std::shared_ptr<Http> spHttp;
public:
    TimeNode(std::shared_ptr<Http> http,int timeout);
    ~TimeNode();
    TimeNode(TimeNode &tn);
    void update(int timeout);
    bool isvaild();
    void clearReq();
    void setDeleted(){ deleted_ = true;}
    bool isDeleted()const {return deleted_;}
    size_t getExpTime()const {return expiredtime_;}
};

struct TimeCmp{
    bool operator()(std::shared_ptr<TimeNode> &a,std::shared_ptr<TimeNode> &b)const {
        return a->getExpTime() > b->getExpTime();
    }
};

//优先队列存储定时器
class TimeManager{
    typedef std::shared_ptr<TimeNode> SPTimeNode;
private:
    std::priority_queue<SPTimeNode,std::deque<SPTimeNode>,TimeCmp> time_node_queue_;
public:
    TimeManager();
    ~TimeManager();
    size_t getMinTime();
    void addTime(std::shared_ptr<Http> http,int timeout);
    void handleExpiredEvents();
};

#endif //MYWEBSERVER_TIME_H
