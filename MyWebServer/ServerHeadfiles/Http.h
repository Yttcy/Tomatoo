//
// Created by yttcy on 2022/4/16.
//

#ifndef MYWEBSERVER_HTTP_H
#define MYWEBSERVER_HTTP_H
#include <memory>
#include "Reactor.h"
#include "../util/Util.h"
#include <map>
#include <string>
#include <sys/stat.h>
#include <unordered_map>
#include <sys/mman.h>
#include <sys/sendfile.h>

class TimeNode;

enum ProcessState {
    STATE_PARSE_URI = 1,
    STATE_PARSE_HEADERS,
    STATE_RECV_BODY,
    STATE_ANALYSIS,
    STATE_FINISH
};

enum URIState {
    PARSE_URI_AGAIN = 1,
    PARSE_URI_ERROR,
    PARSE_URI_SUCCESS,
};

enum HeaderState {
    PARSE_HEADER_SUCCESS = 1,
    PARSE_HEADER_AGAIN,
    PARSE_HEADER_ERROR
};

enum AnalysisState { ANALYSIS_SUCCESS = 1, ANALYSIS_ERROR };

enum ParseState {
    H_START = 0,
    H_KEY,
    H_COLON,
    H_SPACES_AFTER_COLON,
    H_VALUE,
    H_CR,
    H_LF,
    H_END_CR,
    H_END_LF
};

enum ConnectionState { H_CONNECTED = 0, H_DISCONNECTING, H_DISCONNECTED };

enum HttpMethod { METHOD_POST = 1, METHOD_GET, METHOD_HEAD };

enum HttpVersion { HTTP_10 = 1, HTTP_11 };

//也就是不让构造和复制构造
class MimeType{
private:
    static void init();
    static std::unordered_map<std::string,std::string> mime;
    MimeType();
    MimeType(const MimeType &m);
public:
    static std::string getMime(const std::string &key);
private:
    //这个私有变量是干什么的呢。
    static pthread_once_t once_control;
};

//这个enable_shared_from_this主要是解决this和引用计数不放在一起的问题。
class Http:public std::enable_shared_from_this<Http>{
private:
    bool isfile_;
    Reactor *reactor_;
    std::shared_ptr<EventHander> eventHander_;
    int fd_;
    std::string inbuffer_;
    std::string outbuffer_;
    bool error_;
    ConnectionState connectionState_;
    HttpMethod httpMethod_;
    HttpVersion httpVersion_;
    std::string filename_;
    std::string path_;
    int nowReadPos_;
    ProcessState processState_;
    ParseState parseState_;
    bool keepLive_;
    std::map<std::string,std::string> headers_;
    std::weak_ptr<TimeNode> time_;
public:
    Http(Reactor *reactor1,int fd);
    ~Http();
    void reset();
    void seperateTimer();
    void newEvent();
    void handleClose();
    void linkTime(std::shared_ptr<TimeNode> time);
    std::shared_ptr<EventHander> getEventHander(){ return eventHander_;}
    Reactor* getReactor(){return reactor_;}
private:
    void handleRead();
    void handleWrite();
    void handleConn();
    void handleError(int fd,int err_num,std::string msg);
    URIState parseURL();
    HeaderState parseHeaders();
    AnalysisState analysisRequest();
};

#endif //MYWEBSERVER_HTTP_H
