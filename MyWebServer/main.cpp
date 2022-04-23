#include "./ServerHeadfiles/MyServer.h"

#define THREAD_NUM 4

int main() {


//    struct stat sbuf;
//    if(stat("../htmlfiles/index.html",&sbuf) < 0){
//        perror("../htmlfiles/index.html");
//        return -1;
//    }
//    printf("the file size is :%d",sbuf.st_size);

    Reactor reactor;
    MyServer myServer(&reactor,THREAD_NUM,9999);
    myServer.start();
    reactor.dispatch();
    return 0;


}


//没有显示发生了事件，说明一直还是监听状态
//现在该开始进行一个有锁的队列操作，八个线程分别从队列中取走任务。
