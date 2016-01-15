#ifndef THREAD_QUEUE_H_
#define THREAD_QUEUE_H_

#include <deque>
#include <vector>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include<algorithm>
#include "nonablecopy.h"
#include "condition.h"

namespace daocode{
    //线程队列

    class threadQueue:public nonablecopy{
        //typedef std::function< void() > ThreadfuncPtr;
    public:

        typedef std::function< void() > ThreadfuncPtr;

        threadQueue();
        ~threadQueue();
        void start();
        void stop();
        void push_back(ThreadfuncPtr ptr);//加入任务队列
        void Process();//处理任务
        inline void SetMax_size_queue(int max_size_queue_=1024)
        {
            this->max_size_queue = max_size_queue_;
        }
        inline void SetThread_cnt(int thread_cnt_=1)
        {
            this->thread_cnt = thread_cnt_;
        }
        inline void SetIs_start(bool is_start_=false )
        {
            this->is_start = is_start_;
        }

        inline int ThreadCnt()
        {
            return  this->thread_cnt;
        }


        inline std::vector< std::shared_ptr<std::thread> >  & get_work_threads(){
            return work_threads;
        }


    private:

        std::vector< std::shared_ptr<std::thread> > work_threads;//工作线程
        std::deque<ThreadfuncPtr> thrPtrs;
        int max_size_queue;//队列最大数
        int thread_cnt;//线程数
        int is_start;//线程是否开始
        std::mutex mtx;//任务队列锁
        Condition cond;
    };
}

#endif // THREAD_QUEUE_H_
