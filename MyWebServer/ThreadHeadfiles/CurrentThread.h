//
// Created by yttcy on 2022/4/11.
//

#ifndef MYWEBSERVER_CURRENTTHREAD_H
#define MYWEBSERVER_CURRENTTHREAD_H


#include <stdint.h>

namespace CurrentThread {
// internal
    extern __thread int t_cachedTid;
    extern __thread char t_tidString[32];
    extern __thread int t_tidStringLength;
    extern __thread const char* t_threadName;
    void cacheTid();
    inline int tid() {
        //下面这条语句就是告诉编译器， t_cachedTid ！= 0 的概率很大，就是提高速度的。
        if (__builtin_expect(t_cachedTid == 0, 0)) {
            cacheTid();
        }
        return t_cachedTid;
    }

    inline const char* tidString()  // for logging
    {
        return t_tidString;
    }

    inline int tidStringLength()  // for logging
    {
        return t_tidStringLength;
    }

    inline const char* name() { return t_threadName; }
}





#endif //MYWEBSERVER_CURRENTTHREAD_H
