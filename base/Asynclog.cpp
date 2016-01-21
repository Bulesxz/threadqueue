#include "Asynclog.h"
#include <string.h>
#include <iostream>
using namespace daocode;
AsyncLog::AsyncLog()
{
}
AsyncLog::AsyncLog(std::string filename,int rotate_size):file(filename,rotate_size),is_start(false)
{
}

void AsyncLog::init(std::string filename,int rotate_size)
{
    setFilename( filename, rotate_size);
    setRotateSize( rotate_size);
    file.init();
}
AsyncLog::~AsyncLog()
{
    cond.notify_one();
    if (thread_log) thread_log->join();
}
int AsyncLog::start()
{
    is_start=true;
    int ret = file.open();
    if (ret!=0){
        return 1;
    }
    thread_log.reset (new std::thread(std::bind(&AsyncLog::log_write,this)) );
}
void AsyncLog::log_out(const char *data,int len)//多个线程
{
    std::unique_lock <std::mutex> lck (mtx);
 //   char data[64]={0};
   // sprintf(data,"time :%s i:%d \n",__TIME__,i);
    buff.append(data,strlen(data));
    cond.notify_one();
}
void AsyncLog::log_write()//一个线程
{
    std::unique_lock <std::mutex> lck (mtx);
    while (is_start) {
        std::cout<<"while...\n";
        lck.unlock();
        if (buff.readableBytes()==0){
            lck.lock();
            buff.changeIndex();
            lck.unlock();
        }

        while(buff.readableBytes()>0){
            int len = buff.readableBytes();
            std::cout<<buff.GetPeek();
            file.Write(buff.GetPeek(),len);
            buff.seek(len);
        }
        if(buff.readableBytes()==0){
            buff.clearReadbuf();
            buff.resetSeek();
            lck.lock();
            if (!buff.writeBuffRef().empty())
            {
                buff.changeIndex();
                continue;
            }
            lck.unlock();
        }
        lck.lock();
        cond.wait(lck);
    }
}

void AsyncLog::setFilename(std::string filename,int rotate_size)
{
    filename_ = filename;
}
void LogFile::setRotateSize(int rotate_size)
{
    rotate_size_= rotate_size;
}
