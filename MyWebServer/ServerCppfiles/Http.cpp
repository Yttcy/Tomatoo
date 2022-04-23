//
// Created by yttcy on 2022/4/16.
//

#include "../ServerHeadfiles/Http.h"
#include "../ServerHeadfiles/Time.h"

pthread_once_t MimeType::once_control = PTHREAD_ONCE_INIT;
std::unordered_map<std::string, std::string> MimeType::mime;

const __uint32_t DEFAULT_EVENT = EPOLLIN | EPOLLET | EPOLLONESHOT;

//两秒时间不可能出问题啊
const int DEFAULT_EXPIRED_TIME = 2000;              // ms
const int DEFAULT_KEEP_ALIVE_TIME = 1 * 30 * 1000;  // ms 设置默认保持连接的时间是30秒

void MimeType::init() {
    mime[".html"] = "text/html";
    mime[".avi"] = "video/x-msvideo";
    mime[".bmp"] = "image/bmp";
    mime[".c"] = "text/plain";
    mime[".doc"] = "application/msword";
    mime[".gif"] = "image/gif";
    mime[".gz"] = "application/x-gzip";
    mime[".htm"] = "text/html";
    mime[".ico"] = "image/x-icon";
    mime[".jpg"] = "image/jpeg";
    mime[".png"] = "image/png";
    mime[".txt"] = "text/plain";
    mime[".mp3"] = "audio/mp3";
    mime["default"] = "text/html";
}

std::string MimeType::getMime(const std::string &key) {
    //这是让四个线程只来初始化一次
    pthread_once(&once_control,MimeType::init);
    if(mime.find(key) != mime.end()){
        return mime[key];
    }else{
        return mime["default"];
    }
}


Http::Http(Reactor *reactor1, int fd):
isfile_(false),
reactor_(reactor1),
eventHander_(new EventHander(reactor1,fd)),
fd_(fd),
error_(false),
path_("../htmlfiles/"),
connectionState_(H_CONNECTED),
httpMethod_(METHOD_GET),
httpVersion_(HTTP_11),
nowReadPos_(0),
processState_(STATE_PARSE_URI),
parseState_(H_START),
keepLive_(false)
{
    eventHander_->setReadHandle([this] { handleRead();});
    eventHander_->setConnHandle([this] { handleConn(); });
    eventHander_->setWriteHandle([this] { handleWrite(); });
}

Http::~Http() {
    printf("fd_ %d Http destroy\n",fd_);
    close(fd_);
}

void Http::reset() {
    filename_.clear();
    nowReadPos_ = 0;
    processState_ = STATE_PARSE_URI;
    parseState_ = H_START;
    headers_.clear();

    if(time_.lock()){
        std::shared_ptr<TimeNode> timer(time_.lock());
        timer->clearReq();
        timer.reset();
    }

}

//保证线程安全。
void Http::seperateTimer() {
    if(time_.lock()){
        std::shared_ptr<TimeNode> timer(time_.lock());
        timer->clearReq();
        timer.reset();
    }
}

void Http::newEvent() {
    eventHander_->setEvents(DEFAULT_EVENT);
    //设置两秒超时，那keep-alive时间呢
    reactor_->addtoEpoll(eventHander_,DEFAULT_EXPIRED_TIME);
}

void Http::handleClose() {
    connectionState_ = H_DISCONNECTED;
    std::shared_ptr<Http> guard(shared_from_this());
    reactor_->delfromEpoll(eventHander_);
}

void Http::linkTime(std::shared_ptr<TimeNode> time) {
    time_ = time;
}

void Http::handleRead() {
    uint32_t &events = eventHander_->getEvents();
    do{
        bool judge = false;
        int read_num = readn(fd_,inbuffer_,judge);


        //这里加上要写入日志文件。

        //离谱的是你while循环里面是false，那么应该不会设置状态啊
        if(connectionState_ == H_DISCONNECTED){
            inbuffer_.clear();
            break;
        }

        if(read_num < 0){
            perror("1");
            error_ = true;
            handleError(fd_,400,"Bad Request");
            break;
        }else if(judge){
            //这个就是有请求出现但是读不到数据，很大可能是对端关闭了，
            //直接处理对端关闭
            connectionState_ = H_DISCONNECTING;
            if(read_num == 0){
                break;
            }
        }

        if(processState_ == STATE_PARSE_URI){
            URIState flag = this->parseURL();
            if(flag == PARSE_URI_AGAIN){
                break;
            }else if(flag == PARSE_URI_ERROR){
                perror("2");
                //这里写入日志文件
                inbuffer_.clear();
                error_ = true;
                handleError(fd_,400,"Bad Request");
                break;
            }else{
                //这代表状态解析完成了，可以解析头部了。
                processState_ = STATE_PARSE_HEADERS;
            }
        }

        if(processState_ == STATE_PARSE_HEADERS){
            HeaderState hState = this->parseHeaders();
            if(hState == PARSE_HEADER_AGAIN){
                break;
            }else if(hState == PARSE_HEADER_ERROR){
                perror("PARSE_HEADER_ERROR");
                error_ = true;
                handleError(fd_,400,"Bad Request");
                break;
            }

            //如果是客户端是提交表单的话，接受，如果是get请求，就分析
            if(httpMethod_ == METHOD_POST){
                processState_ = STATE_RECV_BODY;
            }else{
                processState_ = STATE_ANALYSIS;
            }
        }

        //如果对方提交的是表单，要先获取长度
        if(processState_ == STATE_RECV_BODY){
            //保存提交表单的长度,这个长度应该是包括头部和内容的
            int content_length = -1;
            if(headers_.find("Content-Length") != headers_.end()){
                content_length = stoi(headers_["Content-Length"]);
            }else{
                error_ = true;
                handleError(fd_,400,"Bad Request:Content-length");
                break;
            }
            if(inbuffer_.size() < content_length)
                break;
            processState_ = STATE_ANALYSIS;
        }

        if(processState_ == STATE_ANALYSIS){
            AnalysisState analysisState = this->analysisRequest();
            if(analysisState == ANALYSIS_SUCCESS){
                processState_ = STATE_FINISH;
                break;
            }else{
                error_ = true;
                perror("analysisRequest failed");
                break;
            }
        }
        //这个条件为什么要false，谁也搞不懂啊
    }while(false);

    if(!error_){
        if(!outbuffer_.empty()){
            handleWrite();
        }
        //这儿的意思是如果同时到达两个请求，那么就清空除了inbuffer_之外的东西，不然就退出
        if(!error_ && processState_ == STATE_FINISH){
            this->reset();
            if(!inbuffer_.empty()){
                if(connectionState_ != H_DISCONNECTED){
                    handleRead();
                }
            }
            //如果设置的是EAGAIN，那么就设置读，设置LT或者ET有没有影响呢。
        }else if(!error_ && connectionState_ != H_DISCONNECTED){
            events |= EPOLLIN;
        }
    }

}

void Http::handleWrite() {
    if(!error_ && connectionState_ != H_DISCONNECTED){
        uint32_t &events_ = eventHander_->getEvents();
        if(writen(fd_,outbuffer_) < 0){
            perror("written");
            events_ = 0;
            error_ = true;
        }
        if(outbuffer_.empty() && httpMethod_ != METHOD_HEAD){
            struct stat sbuf{};
            std::string real_path_filename = path_ + filename_;
            //怎么说呢，这里要stat的话，那么就应该把前面的路劲加上
            //他妈的，这儿怎么会stat错误呢，明明有文件的啊。../htmlfiles/index.html
            if (stat(real_path_filename.c_str(), &sbuf) < 0) {
                printf("%s stat error\n",real_path_filename.c_str());
                handleError(fd_, 404, "Not Found!1");
                return;
            }

            int filefd = open(real_path_filename.c_str(),O_RDONLY,0);
            if(filefd < 0){
                outbuffer_.clear();
                handleError(fd_,404,"Not Found File");
                return;
            }


            //关键是这里对端关闭了吗，那我还要处理SIGPIPE信号啊
            //这里直接发送SIGPIPE信号，直接终止了进程。但是对端怎么会关闭呢！！！，不管了，还是要处理
            //直接个SIGPIPE信号给屏蔽了就可以了，嗯嗯嗯！！

            //就当做对端关闭了，那么就是直接设置error_为true，到时直接处理关闭，就没有问题了。
            long int res = sendfile(fd_,filefd, nullptr,sbuf.st_size);
            if(res == -1){
                error_ = true;
            }
            printf("file : %s sendfile success \n",filename_.c_str());

            close(filefd);
        }
        if(!outbuffer_.empty()){
            //这里是没有写完的话，就设置可以写，
            events_ |= EPOLLOUT;
        }
    }
}

void Http::handleConn() {
    seperateTimer();
    //这个返回的是引用，对这个修改，原来的值也是会修改的。
    uint32_t &events_ = eventHander_->getEvents();
    if(!error_ && connectionState_ == H_CONNECTED){
        //???还有什么情况error_是为0的呢,这应该是正常处理的情况吧！
        //就是更新连接的时间
        if(events_ != 0){
            int timeout = DEFAULT_EXPIRED_TIME;
            if(keepLive_){
                timeout = DEFAULT_KEEP_ALIVE_TIME;
            }
            //这是outbuffer不为空的情况，实在是想不到什么情况会出现这种情况
            if((events_ & EPOLLIN) && (events_ & EPOLLOUT)){
                events_ = uint32_t (0);
                events_ |= EPOLLOUT;
            }
            events_ |= EPOLLET;
            reactor_->updateEpoll(eventHander_, timeout);
            //这是相当于对客户端关闭了连接，但是都想HTTP为什么析构了呢
        }else if(keepLive_){
            events_ |= (EPOLLIN | EPOLLET);
            int timeout = DEFAULT_KEEP_ALIVE_TIME;
            reactor_->updateEpoll(eventHander_,timeout);
        }else{
            events_ |= (EPOLLIN | EPOLLET);
            int timeout = (DEFAULT_KEEP_ALIVE_TIME >> 1);
            reactor_->updateEpoll(eventHander_,timeout);
        }
        //这是关闭连接了，如果还有输出的话
    }else if(!error_ && connectionState_ == H_DISCONNECTED && (events_ & EPOLLOUT)){
        events_ = (EPOLLOUT | EPOLLET);
        //下面这个是对端关闭连接了，没有输入，调用这个HTTP的处理函数
    }else{
        reactor_->runInLoop([this]{this->handleClose();});
    }

}

void Http::handleError(int fd,int err_num,std::string msg) {
    msg = " " + msg;
    char send_buff[4096];
    std::string body_buff, header_buff;
    body_buff += "<html><title>哎~出错了</title>";
    body_buff += "<body bgcolor=\"ffffff\">";
    body_buff += std::to_string(err_num) + msg;
    body_buff += "<hr><em> LinYa3's Web Server</em>\n</body></html>";

    header_buff += "HTTP/1.1 " + std::to_string(err_num) + msg + "\r\n";
    header_buff += "Content-Type: text/html\r\n";
    header_buff += "Connection: Close\r\n";
    header_buff += "Content-Length: " + std::to_string(body_buff.size()) + "\r\n";
    header_buff += "Server: Yangtao4's Web Server\r\n";
    ;
    header_buff += "\r\n";
    // 错误处理不考虑writen不完的情况，现在处理完了错误，怎么做到自动关闭连接的
    sprintf(send_buff, "%s", header_buff.c_str());
    writen(fd, send_buff, strlen(send_buff));
    sprintf(send_buff, "%s", body_buff.c_str());
    writen(fd, send_buff, strlen(send_buff));
}


//可以得到请求类型，版本号，文件名
URIState Http::parseURL() {
    std::string &str = inbuffer_;
    std::string temp = str;

    size_t pos = temp.find('\r',nowReadPos_);
    //如果没有找到回车符号，那么就返回AGAIN，等下次读的时候
    if(pos < 0){
        return PARSE_URI_AGAIN;
    }
    //将第一行单独提取出来
    std::string request_line = str.substr(0,pos);
    if(str.size() > pos + 1){
        //现在的str是下标为pos+1到结尾，？？？那结尾的换行\n不也保存进去了吗，对头部的解析有影响吗？
        //后面验证一下，没必要了，下面状态机有处理
        str = str.substr(pos+1);
    }else{
        str.clear();
    }

    int posGET = request_line.find("GET");
    int posPOST = request_line.find("POST");
    int posHEAD = request_line.find("HEAD");

    if(posGET >= 0){
        pos = posGET;
        httpMethod_ = METHOD_GET;
    }else if(posPOST >= 0){
        pos = posPOST;
        httpMethod_ = METHOD_POST;
    }else if(posHEAD >= 0){
        pos = posHEAD;
        httpMethod_ = METHOD_HEAD;
    }else{
        return PARSE_URI_ERROR;
    }

    //接下来解析客户端想要的文件。
    pos = request_line.find("/",pos);
    //如果没有找到，那么就设置默认属性
    if(pos < 0){
        filename_ = "index.html";
        httpVersion_ = HTTP_11;
        return PARSE_URI_SUCCESS;
    }else{
        size_t _pos = request_line.find(' ',pos);
        //这个是/之后的文件名
        if(_pos - pos > 1){
            filename_ = request_line.substr(pos+1,_pos-pos-1);
            //这个问号是分隔url和查询参数的，所以要去掉
            size_t __pos = filename_.find('?');
            if (__pos >= 0) {
                filename_ = filename_.substr(0, __pos);
            }
        }else{
            filename_ = "index.html";
        }
        pos = _pos;
    }
    pos = request_line.find('/',pos);
    if(pos < 0){
        return PARSE_URI_ERROR;
    }else{
        //request_line是保存了\r的，下面相减应该是大于3的
        if(request_line.size() - pos <= 3){
            return PARSE_URI_ERROR;
        }else{
            //所以说这就是直接看能不能到3
            std::string version = request_line.substr(pos+1,3);
            if(version == "1.0"){
                httpVersion_ = HTTP_10;
            }else if(version == "1.1"){
                httpVersion_ = HTTP_11;
            }else{
                return PARSE_URI_ERROR;
            }
        }
    }
    return PARSE_URI_SUCCESS;
}

HeaderState Http::parseHeaders() {
    std::string &str = inbuffer_;
    int key_start = -1;
    int key_end = -1;
    int value_start = -1;
    int value_end = -1;
    int now_read_line_begin = 0;
    bool notfinished = true;
    size_t i=0;
    for(;i<str.size() && notfinished;++i){
        switch(parseState_){
            case H_START:{
                if(str[i] == '\n' || str[i] == '\r'){
                    break;
                }
                parseState_ = H_KEY;
                key_start = i;
                now_read_line_begin = i;
                break;
            }

            //现在是子得到key值，满足左开右闭的原则
            case H_KEY:{
                if(str[i] == ':'){
                    key_end = i;
                    //一般不会出现下面这种情况吧
                    if(key_end - key_start <= 0){
                        return PARSE_HEADER_ERROR;
                    }
                    parseState_ = H_COLON;
                }else if(str[i] == '\r' || str[i] == '\n'){
                    return PARSE_HEADER_ERROR;
                }
                break;
            }

            //这个是在处理：后面的空格
            case H_COLON:{
                if(str[i] == ' '){
                    parseState_ = H_SPACES_AFTER_COLON;
                }else{
                    return PARSE_HEADER_ERROR;
                }
                break;
            }

            //这个好像不是必须的。错了，是拿来处理value_start的，
            case H_SPACES_AFTER_COLON:{
                parseState_ = H_VALUE;
                value_start = i;
                break;
            }

            //获取到value值
            case H_VALUE:{
                if(str[i] == '\r'){
                    value_end = i;
                    parseState_ = H_CR;
                    if(value_end - value_start <= 0){
                        return PARSE_HEADER_ERROR;
                    }
                }else if(i - value_start > 255){
                    return PARSE_HEADER_ERROR;
                }
                break;
            }

            //这里将键值对添加到map里面去
            case H_CR:{
                if(str[i] == '\n'){
                    parseState_ = H_LF;
                    std::string key(str.begin()+key_start,str.begin()+key_end);
                    std::string value(str.begin()+value_start,str.begin()+value_end);
                    headers_[key] = value;
                    now_read_line_begin = i;
                }else{
                    return PARSE_HEADER_ERROR;
                }
                break;
            }

            //如果是\r那么就是到结尾了，不是，说明还有没解析完成的。
            case H_LF: {
                if (str[i] == '\r') {
                    parseState_ = H_END_CR;
                } else {
                    key_start = i;
                    parseState_ = H_KEY;
                }
                break;
            }

            case H_END_CR: {
                if (str[i] == '\n') {
                    parseState_ = H_END_LF;
                } else
                    return PARSE_HEADER_ERROR;
                break;
            }

            //这就是如果缓冲区不止一个请求，那么就会进入这个，主动结束循环
            //不切换状态了，直接以这个状态退出循环。
            case H_END_LF:{
                notfinished = false;
                key_start = i;
                now_read_line_begin = i;
                break;
            }

        }
    }
    if(parseState_ == H_END_LF){
        str = str.substr(i);
        return PARSE_HEADER_SUCCESS;
    }
    str = str.substr(now_read_line_begin);
    return PARSE_HEADER_AGAIN;
}



AnalysisState Http::analysisRequest() {
    if(httpMethod_ == METHOD_POST){

    }else if(httpMethod_ == METHOD_GET || httpMethod_ == METHOD_HEAD){
        std::string respond_header;
        respond_header += "HTTP/1.1 200 OK\r\n";
        if(headers_.find("Connection") != headers_.end() &&
        headers_["Connection"] == "keep-alive"
        ){
            keepLive_ = true;
            respond_header += "Connection: keep-alive\r\n";
            respond_header += "Keep-Alive: timeout="+std::to_string(DEFAULT_KEEP_ALIVE_TIME)+"\r\n";
        }
        size_t dot_pos = filename_.find('.');
        std::string filetype;
        if(dot_pos<0){
            filetype = MimeType::getMime("default");
        }else{
            filetype = MimeType::getMime(filename_.substr(dot_pos));
        }

//        //这儿测试一下
//        if(filename_ == "index.html"){
//            outbuffer_ += "HTTP/1.1 200 OK\r\n";
//            outbuffer_ += "Content-type: text/plain\r\n\r\n";
//            outbuffer_ += "Yes I successs!!!";
//            return ANALYSIS_SUCCESS;
//        }
        struct stat sbuf{};
        std::string real_path_filename = path_ + filename_;
        //怎么说呢，这里要stat的话，那么就应该把前面的路劲加上
        //他妈的，这儿怎么会stat错误呢，明明有文件的啊。../htmlfiles/index.html
        if (stat(real_path_filename.c_str(), &sbuf) < 0) {
            respond_header.clear();
            printf("%s stat error\n",real_path_filename.c_str());
            handleError(fd_, 404, "Not Found!1");
            return ANALYSIS_ERROR;
        }

        respond_header += "Content-Type: " + filetype + "\r\n";
        respond_header += "Content-Length: " + std::to_string(sbuf.st_size) + "\r\n";
        respond_header += "Server: Tomatoo web server !!!\r\n";
        respond_header += "\r\n";
        //到这里头部结束了
        outbuffer_ += respond_header;
        if(httpMethod_ == METHOD_HEAD){
            return ANALYSIS_SUCCESS;
        }

        //全部都交给sendfile处理
        isfile_ = true;
        return ANALYSIS_SUCCESS;

        //added by Tomatoo


//        int filefd = open(real_path_filename.c_str(),O_RDONLY,0);
//        if(filefd < 0){
//            outbuffer_.clear();
//            handleError(fd_,404,"Not Found File");
//            return ANALYSIS_ERROR;
//        }
//
//        //因为用户空间要加上一些头部信息，所以没办法用sendfile，可以用mmap+write
//        //现在问题来了，mmap成功了，但是src——addr的长度是1，这是怎么回事呢。
//        //而且subf.st_size 的结果是1150，说明是映射错误咯
//        void *src_addr = mmap(nullptr,sbuf.st_size,PROT_READ,MAP_PRIVATE,filefd,0);
//        if(src_addr == MAP_FAILED){
//            munmap(src_addr,sbuf.st_size);
//            outbuffer_.clear();
//            handleError(fd_,404,"mmap Error!!!");
//            return ANALYSIS_ERROR;
//        }
//
//
//        char *real_src_addr = (char *)src_addr;
//        outbuffer_ += real_src_addr;
//        munmap(src_addr,sbuf.st_size);
//
//        return ANALYSIS_SUCCESS;
    }else{
        return ANALYSIS_ERROR;
    }
    return ANALYSIS_ERROR;
}