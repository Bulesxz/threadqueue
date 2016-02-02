#ifndef TIMER_H
#define TIMER_H
#include<functional>
#include<atomic>

typedef std::function<void(void)> TimerCallback;
typedef long Timestamp;

class Timer{

 public:
    Timer(TimerCallback& callback,Timestamp when,int64_t interval):
        callback_(callback),expire_(when),sequence_(++timer_numCreated_),
        interval_(interval),repeat_(interval>0){}
    void run();
    void restart(Timestamp now);

private:
    TimerCallback callback_;
    Timestamp expire_;
    const long sequence_;
    long interval_;
    bool repeat_;
    static std::atomic_long timer_numCreated_;
};
#endif // TIMER_H
