#ifndef CONDITION_H
#define CONDITION_H

#include <condition_variable>
#include <mutex>
#include <nonablecopy.h>
namespace daocode{
class Condition:public nonablecopy {
public:
    Condition(){}
    ~Condition(){}
    inline void notify_one(){
        condition.notify_one();
    }
    inline void notify_all(){
        condition.notify_all();
    }
    inline void wait(std::unique_lock<std::mutex> &lck){
        condition.wait(lck);
    }
private:
    std::condition_variable condition;
};
}
#endif // CONDITION_H
