#include "logger.h"
using namespace daocode;
Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::set_level(int level)
{
    level_ = level;
}

bool Logger::check_level(int level)
{
    return level>=level_;//大于当前设置的级别
}


void Logger::log_write(LogLevel level,const char* filename,int line,const char* func,const char* fmt, ...)
{
    if ( !check_level(level) ){
        return ;
    }

    va_list ap;
    va_start(ap, fmt);
    char buf[4096];
    vsnprintf(buf, 4096, fmt, ap);
    log_out(level, filename, line, func, buf);
    va_end(ap);
}

void Logger::log_out(LogLevel level,const char* filename,int line,const char* func,const char *msg)
{
      printf("log_level=%d|%s|%d|%s|%s\n", level, filename, line, func, msg);
}
