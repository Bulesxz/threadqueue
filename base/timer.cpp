#include "timer.h"

#include <sys/timerfd.h>

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
    struct timeval us;
    gettimeofday(&us,NULL);
    return Timestamp(us.tv_sec*1000000 + us.tv_usec);
}

timeval TimestampTotimeval(Timestamp microseconds)
{
    struct timeval tl;
    tl.tv_sec = microseconds/1000000;
    tl.tv_usec = microseconds%1000000;
    return tl;
}
struct timeval howMuchTimeFromNow(Timestamp when)
{
    Timestamp microseconds = when - Now();
    return TimestampTotimeval(microseconds);
}

void resetTimerfd(int timerfd, Timestamp expiration)
{
  // wake up loop by timerfd_settime()
  struct itimerspec newValue;
  struct itimerspec oldValue;
  bzero(&newValue, sizeof newValue);
  bzero(&oldValue, sizeof oldValue);
  newValue.it_value = howMuchTimeFromNow(expiration);
  int ret = ::timerfd_settime(timerfd, 0/*相对时间*/, &newValue, &oldValue);
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
