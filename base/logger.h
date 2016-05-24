#ifndef LOGGER_H
#define LOGGER_H
#include <log.h>
#include <iostream>
namespace daocode{

class BaseLogger{
public:
    BaseLogger();
    virtual ~BaseLogger();
public:
    virtual void write(LogLevel level,const char* filename,int line,const char* func,const char *msg);
    virtual void log_write(LogLevel level,const char* filename,int line,const char* func,const char* fmt,...);
    virtual int start(){return 0;};
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
    ~CSingletonLogger(){}
    static BaseLogger *logger_;
public:
    static CSingletonLogger * GetInstance()
    {
        static  CSingletonLogger m_instance;
        return &m_instance;
    }

    BaseLogger *get_logger()
    {
        if (logger_!=NULL)
            return logger_;
        else
            return NULL;
    }
    void set_logger(BaseLogger *loger)
    {
        logger_ = loger;
    }

    class CGarbo //它的唯一工作就是在析构函数中删除CSingleton的实例
    {
        public:
            ~CGarbo()
            {
                std::cout<<"~m_instance\n";
                if(CSingletonLogger::GetInstance()->get_logger()){
                    delete CSingletonLogger::GetInstance()->get_logger();
                }
            }
    };
private:
    static CGarbo Garbo; //定义一个静态成员，程序结束时，系统会自动调用它的析构函数
};

#define LOG_TRACE(fmt,...)    \
        daocode::CSingletonLogger::GetInstance()->get_logger()->log_write(LEVEL_TRACE, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
#define LOG_DEBUG(fmt,...)    \
        daocode::CSingletonLogger::GetInstance()->get_logger()->log_write(LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
#define LOG_INFO(fmt,...)    \
        daocode::CSingletonLogger::GetInstance()->get_logger()->log_write(LEVEL_INFO,  __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
#define LOG_WARN(fmt,...)    \
        daocode::CSingletonLogger::GetInstance()->get_logger()->log_write(LEVEL_WARN,  __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
#define LOG_ERROR(fmt,...)    \
        daocode::CSingletonLogger::GetInstance()->get_logger()->log_write(LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
#define LOG_FATAL(fmt,...)    \
        daocode::CSingletonLogger::GetInstance()->get_logger()->log_write(LEVEL_FATAL, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)

}

#endif // LOGGER_H
