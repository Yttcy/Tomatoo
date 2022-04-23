//
// Created by yttcy on 2022/4/16.
//

#include "../ServerHeadfiles/Time.h"

TimeNode::TimeNode(std::shared_ptr<Http> http, int timeout):
spHttp(http),
deleted_(false)
{
    struct timeval now;
    gettimeofday(&now, nullptr);
    //如果这里用毫秒来计算不怕越界吗
    //现在expiredtime得到的就是超时的时间了。
    expiredtime_ = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

TimeNode::~TimeNode() {
    if(spHttp){
        spHttp->handleClose();
    }
}

TimeNode::TimeNode(TimeNode &tn):
spHttp(tn.spHttp),
expiredtime_(0)
{

}

void TimeNode::update(int timeout) {
    struct timeval now;
    gettimeofday(&now, nullptr);
    expiredtime_ = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

bool TimeNode::isvaild() {
    struct timeval now;
    gettimeofday(&now, nullptr);
    size_t temp = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000));
    if(temp < expiredtime_){
        return true;
    }else{
        this->setDeleted();
        return false;
    }
}

//这儿保存的http对象被释放掉了，但是EventHander那儿还没有释放掉
void TimeNode::clearReq() {
    spHttp.reset();
    this->setDeleted();
}


TimeManager::TimeManager() {

}

TimeManager::~TimeManager() {

}


void TimeManager::addTime(std::shared_ptr<Http> http, int timeout) {
    SPTimeNode new_node(new TimeNode(http,timeout));
    time_node_queue_.push(new_node);
    http->linkTime(new_node);
}

size_t TimeManager::getMinTime() {
    if(time_node_queue_.empty()){
        //如果没有超时事件的话，那么就设置为-1，一直等待下去。
        //当有新的事件到来的时候，Reactor会wakeup重新设置的，逻辑上应该是没有问题的。
        return -1;
    }
    struct timeval time_temp;
    gettimeofday(&time_temp, nullptr);
    size_t time_now_ms = (((time_temp.tv_sec % 10000) * 1000) + (time_temp.tv_usec / 1000));
    //如果这里小于0怎么办,如果是小于0的话，那么就是已经超时了，直接设置为0，立即返回，处理超时事件。
    size_t res = time_node_queue_.top()->getExpTime() - time_now_ms;
    return res <= 0? 0 : res;
}

void TimeManager::handleExpiredEvents() {
    while(!time_node_queue_.empty()){
        SPTimeNode time = time_node_queue_.top();
        if(time->isDeleted()){
            time_node_queue_.pop();
        }else if(!time->isvaild()){
            time_node_queue_.pop();
        }else{
            break;
        }
    }
}