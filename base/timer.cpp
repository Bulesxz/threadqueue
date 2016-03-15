#include "timer.h"
#include <iostream>
#include <sys/timerfd.h>
#include <sys/time.h>
#include <strings.h>

std::atomic_long Timer::timer_numCreated_(0);


int createTimerfd()
{
  int timerfd = ::timerfd_create(CLOCK_MONOTONIC,
                                 TFD_NONBLOCK | TFD_CLOEXEC);
  if (timerfd < 0)
  {
    std::cout<< "Failed in timerfd_create\n";
  }
  return timerfd;
}


Timestamp Now()
{
    struct timespec ns={0, 0};  
    clock_gettime(CLOCK_REALTIME, &ns);  
    return Timestamp(ns.tv_sec*1000000000 + ns.tv_nsec);
}

timespec TimestampTotimespec(Timestamp nsec)
{
    struct timespec ts;
    ts.tv_sec = nsec/1000000000;
    ts.tv_nsec = nsec%1000000000;
    return ts;
}
struct timespec howMuchTimeFromNow(Timestamp when)
{
    Timestamp nsec = when - Now();
    return TimestampTotimespec(nsec);
}

void resetTimerfd(int timerfd, Timestamp expiration)
{
  // wake up loop by timerfd_settime()
  struct itimerspec newValue;
  struct itimerspec oldValue;
  bzero(&newValue, sizeof newValue);
  bzero(&oldValue, sizeof oldValue);
  newValue.it_value = howMuchTimeFromNow(expiration);//¿¿¿¿¿¿¿
  int ret = ::timerfd_settime(timerfd, 0/*Ïà¶ÔÊ±¼ä*/, &newValue, &oldValue);
  if (ret)
  {
    std::cout << "timerfd_settime()";
  }
}

void Timer::run()
{
    callback_();
}
void Timer::restart(Timestamp now)
{
    if(repeat_){
        expire_ = now +interval_;
    }
}
