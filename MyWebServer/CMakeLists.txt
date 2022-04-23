cmake_minimum_required(VERSION 3.19)
project(MyWebServer)


set(SERVERHEADFILES
        ServerHeadfiles/MyServer.h
        ServerHeadfiles/Reactor.h
        ServerHeadfiles/EventHander.h
        ServerHeadfiles/Epoll.h
        ServerHeadfiles/Http.h
        ServerHeadfiles/Time.h)

set(SERVERCPPFILES
        ServerCppfiles/MyServer.cpp
        ServerCppfiles/Reactor.cpp
        ServerCppfiles/EventHander.cpp
        ServerCppfiles/Epoll.cpp
        ServerCppfiles/Http.cpp
        ServerCppfiles/Time.cpp
        )

set(THREADHEADFILES
        ThreadHeadfiles/Thread.h
        ThreadHeadfiles/MutexLock.h
        ThreadHeadfiles/CurrentThread.h
        ThreadHeadfiles/Condition.h
        ThreadHeadfiles/CountDownLatch.h
        ThreadHeadfiles/ReactorThread.h
        ThreadHeadfiles/ReactorThreadPool.h)

set(THREADCPPFILES
        ThreadCppfiles/Thread.cpp
        ThreadCppfiles/ReactorThread.cpp
        ThreadCppfiles/ReactorThreadPool.cpp)

set(UTILFILES
        util/Util.h
        util/Util.cpp
        )

set(CMAKE_CXX_STANDARD 14)


add_executable(MyWebServer main.cpp
        ${SERVERHEADFILES}
        ${SERVERCPPFILES}
        ${THREADHEADFILES}
        ${THREADCPPFILES}
        ${UTILFILES}
        test/test.cpp test/test.h)

target_link_libraries(MyWebServer pthread)