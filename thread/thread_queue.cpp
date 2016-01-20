#include "thread_queue.h"

#include<iostream>

using namespace daocode;

threadQueue::threadQueue():max_size_queue(1024),thread_cnt(5),is_start(0)
{
}
threadQueue::~threadQueue()
{
    stop();
    std::cout<<"~threadQueue...\n";
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
            std::cout<<"Process  \n";
            ThreadfuncPtr work = thrPtrs.front();
            thrPtrs.pop_front();
            lck.unlock();
            work();
            lck.lock();
        }
        std::cout<<"wait\n";
        cond.wait(lck);
    }

    std::cout<<"Process...\n";
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

void threadQueue::stop()
{
    std::cout<<"stop\n";
    if(!is_start)
        return ;
    is_start=false;
    cond.notify_all();//如果在cond.wait之前发，导致阻塞在cond.wait

    for(int i=0;i<(int)work_threads.size();i++){
        if (work_threads[i]->joinable())
            work_threads[i]->join();//如果任务干完了，阻塞在这里还可，如果没干完，阻塞则导致notify_all，发出后接收不到
        //work_threads[i]->detach();
    }


    std::cout<<"stop...\n";
}
