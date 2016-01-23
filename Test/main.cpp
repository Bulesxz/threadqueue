#include <iostream>

#include <thread_queue.h>
#include <stdio.h>

#include <unistd.h>
#include <Asynclog.h>

using namespace std;

using namespace daocode;

daocode::threadQueue queue;

void Eventhandle(const char *data,const int len)
{
    LOG_ERROR("data :%s len :%d",data,len);
    //printf("Eventhandle %s %d------------- thread id %d\n",data,len,std::this_thread::get_id());
}

void Produce()
{
    int i=200;
    while(i--){
        queue.push_back(std::bind(&Eventhandle,"123456",i));
    }
}

void Produce1()
{
    int i=10;
    while(i-- ){
        queue.push_back(std::bind(&Eventhandle,"123456",i));
    }
    std::cout<<"Produce\n";
}

int main()
{

    CSingletonLogger::GetInstance()->set_logger(new AsyncLog("test.log",100000));
    CSingletonLogger::GetInstance()->get_logger()->set_level(LEVEL_TRACE);
    CSingletonLogger::GetInstance()->get_logger()->start();

    queue.start();
    cout << "Hello world!.....begin" << endl;
    usleep(1000);
    //queue.push_back(std::bind(&Eventhandle,"12356",6));

    std::thread pthread(std::bind(&Produce));
    pthread.detach();
    //pthread.join();//会阻塞主线程，的queue析构 error

    //LOG_ERROR("data :%s len :%d","aaaaaaaa",100);
    //LOG_ERROR("data :%s len :%d","aaaaaaaa",100);


  /*  std::vector< std::shared_ptr<std::thread> > &work_threads=queue.get_work_threads();
    for (int i=0;i<(int)work_threads.size();i++){
        work_threads[i]->join();
    }*/

    //while(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));//等待任务干完
    return 0;
}
