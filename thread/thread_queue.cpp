#include "thread_queue.h"

#include<iostream>

using namespace daocode;

threadQueue::threadQueue():max_size_queue(1024),thread_cnt(1),is_start(0)
{
}
threadQueue::~threadQueue()
{
}


void threadQueue::push_back(const ThreadfuncPtr ptr)
{
    std::cout<<"threadQueue\n";
    std::unique_lock <std::mutex> lck (mtx);
    if (thrPtrs.size() < (size_t)max_size_queue)
    {
        thrPtrs.push_back(ptr);
         cond.notify_one();
    }
    std::cout<<"threadQueue...\n";
}
void threadQueue::Process()
{
    std::unique_lock <std::mutex> lck (mtx);
    while(is_start){
        //std::unique_lock <std::mutex> lck (mtx);
        while(!thrPtrs.empty()){
            ThreadfuncPtr work = thrPtrs.front();
            thrPtrs.pop_front();
            lck.unlock();
            work();
            lck.lock();
        }
        cond.wait(lck);
    }
}
void threadQueue::start()
{
    std::cout<<"start\n";
    if (!is_start){
        is_start=true;
        for (int i=0;i<thread_cnt;i++){
            std::shared_ptr<std::thread> thrptr (new std::thread(std::bind(&threadQueue::Process,this)));
            work_threads.push_back(thrptr);
        }
    }
    std::cout<<"start....\n";
}
