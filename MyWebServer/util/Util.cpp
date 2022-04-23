//
// Created by yttcy on 2022/4/9.
//



#include "Util.h"

ssize_t readn(int fd,std::string &dst,bool &judge){
    long thisread = 0;
    long readsum = 0;
    while(true){
        char buff[MAX_BUFF];
        if((thisread = read(fd,buff,MAX_BUFF)) < 0){
            if(errno == EINTR){
                continue;
            }else if(errno == EAGAIN){
                return readsum;
            }else{
                return -1;
            }
        }else if(thisread == 0){
            judge = true;
            break;
        }
        readsum += thisread;
        dst = std::string(buff,buff+thisread);
    }
    return readsum;
}

ssize_t readn(int fd,std::string &dst){
    long thisread = 0;
    long readsum = 0;
    while(true){
        char buff[MAX_BUFF];
        if((thisread = read(fd,buff,MAX_BUFF)) < 0){
            if(errno == EINTR){
                continue;
            }else if(errno == EAGAIN){
                return readsum;
            }else{
                return -1;
            }
        }else if(thisread == 0){
            break;
        }
        readsum += thisread;
        dst = std::string(buff,buff+thisread);
    }
    return readsum;
}

ssize_t readn(int fd,void *buff,size_t len){
    ulong nleft = len;
    long thisread = 0;
    long readsum = 0;
    char *ptr = (char *)buff;
    while(nleft > 0){
        if((thisread = read(fd,ptr,len)) < 0){
            if(errno == EINTR){
                thisread = 0;
            }else if(errno == EAGAIN){
                return readsum;
            }else{
                return -1;
            }
        }else if(thisread == 0){
            break;
        }
        nleft -= thisread;
        readsum += thisread;
        ptr += thisread;
    }
    return readsum;
}

ssize_t writen(int fd,std::string &buff){
    long write_sum = 0;
    ulong nleft = buff.size();
    long thiswrite;
    const char *ptr = buff.c_str();
    while(nleft > 0){
        if((thiswrite = write(fd,ptr,nleft)) <= 0){
            if(thiswrite < 0){
                if(errno == EINTR){
                    thiswrite = 0;
                    continue;
                }else if(errno == EAGAIN){
                    //让再次尝试为什么要退出呢。???
                    //说不过去啊。
                    break;
                }else{
                    return -1;
                }
            }
        }
        write_sum += thiswrite;
        nleft -= thiswrite;
        ptr += thiswrite;
    }
    //清除字符串已经发送的部分，好让EAGAIN错误在进入的时候不会重复的写。no problem
    if(write_sum == buff.size()){
        buff.clear();
    }else{
        buff = buff.substr(write_sum);
    }
    return write_sum;
}


ssize_t writen(int fd,void *buff,int num){
    ulong nleft = num;
    long thiswrite = 0;
    long writesum = 0;
    char *ptr = (char *)buff;
    while(nleft > 0){
        if((thiswrite = write(fd,ptr,nleft)) <= 0){
            if(errno == EINTR){
                thiswrite = 0;
                continue;
            }else if(errno == EAGAIN){
                break;
            }else{
                return -1;
            }
        }
        nleft -= thiswrite;
        writesum += thiswrite;
        ptr += thiswrite;
    }
    //这个是传入的直接是指针，所以可以直接返回
    //指针已经被更新了
    return writesum;
}

int socket_bind_listen(int port){

    //如果端口号不正确，直接退出
    if(port < 0 || port > 65535){
        return -1;
    }
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    //初始化套接字失败，也直接退出
    if(listenfd == -1) {
        printf("initial the socket error\n");
        return -1;
    }
    //绑定地址端口号
    struct sockaddr_in sock{};
    bzero(&sock,sizeof(sock));
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = htonl(INADDR_ANY);


    //设置地址重用，防止bind的时候报错
    //默认关闭保持连接选项
    int optval = 1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval)) < 0){
        printf("setsockopt error\n");
        close(listenfd);
        return -1;
    }

    socklen_t length = sizeof(sock);
    if((bind(listenfd,(struct sockaddr *)&sock,length) < 0)){
        printf("bind error\n");
        return -1;
    }

    if(listen(listenfd,MAX_LISTEN) < 0){
        printf("listen error\n");
        close(listenfd);
        return -1;
    }

    return listenfd;
}

//设置套接字为非阻塞的，返回原来的设置遵循规范
int setnonblocking(int sockfd){
    int old_option = fcntl(sockfd,F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(sockfd,F_SETFL,new_option);
    return old_option;
}

void closeNagleAlgh(int sockfd){
    int enable = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (void *)&enable, sizeof(enable));
}