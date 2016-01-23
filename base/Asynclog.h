#ifndef ASYNCLOG_H
#define ASYNCLOG_H

#include <Buffer.h>
#include <condition.h>
#include <logfile.h>
#include <thread>
#include <mutex>
#include <nonablecopy.h>
#include <string>
#include <logger.h>
#include <log.h>
namespace daocode{

class AsyncLog: public nonablecopy,public BaseLogger {
public:
    AsyncLog(std::string filename,int rotate_size);
    ~AsyncLog();
     void log_write();
     void log_out(const char *data,int len);
    int start();
    void write(LogLevel level,const char* filename,int line,const char* func,const char *msg);
private:
    LogFile file;
    Buffer buff;
    Condition cond;
    std::mutex mtx;
    bool is_start;
    std::shared_ptr<std::thread> thread_log;
};

}
#endif // ASYNCLOG_H
