#ifndef TYPEDEF_H
#define TYPEDEF_H
#include <functional>//仿函数
#include <unistd.h>//linix 系统调用
#include <thread>//线程
#include <mutex> //锁相关
#include <memory> //智能指针相关
#include <iostream>
#include <assert.h>
#include <string.h>
#include <strings.h>
typedef long Timestamp;//纳秒
typedef std::function<void()> TimerCallback;
typedef  std::function<void()> Callback;

typedef std::function<void(Timestamp)>  ReadEventCallback;
typedef std::function<void(void)>  EventCallback ;

static inline Timestamp Now()
{
    struct timespec ns={0, 0};
    clock_gettime(CLOCK_REALTIME, &ns);
    return Timestamp(ns.tv_sec*1000000000 + ns.tv_nsec);
}

#endif
