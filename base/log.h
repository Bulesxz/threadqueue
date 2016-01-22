#ifndef LOG_H
#define LOG_H
#include <stddef.h>
namespace daocode{
enum LogLevel
{
    LEVEL_TRACE=0,
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARN,
    LEVEL_ERROR,
    LEVEL_FATAL
};


}
#endif // LOG_H
