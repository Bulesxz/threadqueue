#ifndef LOGGER_H
#define LOGGER_H

namespace daocode{
enum LogLevel
{
    LEVEL_TRACE=1;
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARN,
    LEVEL_ERROR,
    LEVEL_FATAL
};

class Logger{
    virtual void log_out(LogLevel level,const char* filename,int line,const char* func,const char *msg)
    virtual void log_write(LogLevel level,const char* filename,int line,const char* func,const char* fmt,...);
    void set_level(int level);
private:
    bool check_level(int level);
    int curr_level;
};

class CSingletonLogger
{
private:
    CSingletonLogger()   //构造函数是私有的
    {
    }
    static Logger *logger_;
public:
    static Logger * GetInstance()
    {
        if(logger == NULL)  //判断是否第一次调用
            logger = new AsyncLog();
        return logger_;
    }
};
}
#define LOG_TRACE(fmt,...)    \
        simcode::GlobalLogger::logger().log_write(daocode::LogLevel::LEVEL_TRACE, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
#define LOG_DEBUG(fmt,...)    \
        simcode::GlobalLogger::logger().log_write(daocode::LogLevel::LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
#define LOG_INFO(fmt,...)    \
        simcode::GlobalLogger::logger().log_write(daocode::LogLevel::LEVEL_INFO,  __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
#define LOG_WARN(fmt,...)    \
        simcode::GlobalLogger::logger().log_write(daocode::LogLevel::LEVEL_WARN,  __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
#define LOG_ERROR(fmt,...)    \
        simcode::GlobalLogger::logger().log_write(daocode::LogLevel::LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
#define LOG_FATAL(fmt,...)    \
        simcode::GlobalLogger::logger().log_write(daocode::LogLevel::LEVEL_FATAL, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)

#endif // LOGGER_H
