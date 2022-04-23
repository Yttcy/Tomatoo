//
// Created by yttcy on 2022/4/9.
//

#ifndef MYWEBSERVER_UTIL_H
#define MYWEBSERVER_UTIL_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <string>
#include <cstdio>
#include <fcntl.h>
#include <cstring>



#define MAX_LISTEN 2048
#define MAX_BUFF 2048

int socket_bind_listen(int port);
int setnonblocking(int sockfd);
void closeNagleAlgh(int sockfd);
ssize_t writen(int fd,std::string &buff);
ssize_t writen(int fd,void *ptr,int num);
ssize_t readn(int fd,void *buff,size_t len);
ssize_t readn(int fd,std::string &dst,bool &);
ssize_t readn(int fd,std::string &dst);


class noncopyable{
public:
    noncopyable(){};
    ~noncopyable(){};

private:
    noncopyable(const noncopyable& noncopyable1);
    const noncopyable operator=(const noncopyable non);

};




#endif //MYWEBSERVER_UTIL_H
