#include <iostream>

#include <thread_queue.h>
#include <stdio.h>
using namespace std;

daocode::threadQueue queue;

void Eventhandle(const char *data,const int len)
{
    printf("Eventhandle %s %d-------------\n",data,len);
}

void Produce()
{
    int i=1000;
    while(i--){
        queue.push_back(std::bind(&Eventhandle,"123456",i));
    }
}

void Produce1()
{
    int i=2000;
    while(i-- >1000){
        queue.push_back(std::bind(&Eventhandle,"123456",i));
    }
}

int main()
{

    cout << "Hello world!.....begin" << endl;


    queue.start();


    //queue.push_back(std::bind(&Eventhandle,"12356",6));

    std::thread pthread(std::bind(&Produce));
    pthread.join();

    std::thread pthread1(std::bind(&Produce1));
    pthread1.join();

    std::vector< std::shared_ptr<std::thread> > &work_threads=queue.get_work_threads();
    for (int i=0;i<(int)work_threads.size();i++){
        work_threads[i]->join();
    }

    return 0;
}
