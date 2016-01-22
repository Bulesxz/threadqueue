#include <Asynclog.h>
#include <string.h>
#include <iostream>
using namespace daocode;

char LOG[6][8]={"TRACE","DEBUG","INFO","WARN","ERROR","FATAL"};

AsyncLog::AsyncLog(std::string filename,int rotate_size):file(filename,rotate_size),is_start(false)
{
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
    return 0;
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

void AsyncLog::write(LogLevel level,const char* filename,int line,const char* func,const char *msg)
{
    char buf[4096]={0};
    int len = snprintf(buf, 4096,"[%s %s %d %s %s \n]",LOG[level],filename,line,func,msg);
    log_out(buf,len);
}
