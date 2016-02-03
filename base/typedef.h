#ifndef TYPEDEF_H
#define TYPEDEF_H
#include<functional>
#include<memory>
#include <unistd.h>
typedef long Timestamp;//纳秒
typedef std::function<void()> TimerCallback;
typedf  std::function<void()> Callback;
#endif
