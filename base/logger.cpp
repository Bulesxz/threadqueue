#include <logger.h>
#include <stdarg.h>
#include<stdio.h>

using namespace daocode;
CSingletonLogger* CSingletonLogger::m_instance=NULL;
BaseLogger * CSingletonLogger::logger_=NULL;
BaseLogger::BaseLogger()
{

}

BaseLogger::~BaseLogger()
{

}

void BaseLogger::set_level(int level)
{
    curr_level = level;
}

bool BaseLogger::check_level(int level)
{
    return level>=curr_level;//大于当前设置的级别
}


void BaseLogger::log_write(LogLevel level,const char* filename,int line,const char* func,const char* fmt, ...)
{
    if ( !check_level(level) ){
        return ;
    }

    va_list ap;
    va_start(ap, fmt);
    char buf[4096];
    vsnprintf(buf, 4096, fmt, ap);
    write(level, filename, line, func, buf);
    va_end(ap);
}

void BaseLogger::write(LogLevel level,const char* filename,int line,const char* func,const char *msg)
{
      printf("log_level=%d|%s|%d|%s|%s\n", level, filename, line, func, msg);
}
