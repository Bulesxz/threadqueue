#ifndef LOGFILE_H
#define LOGFILE_H
#include<stdio.h>
#include <string>
namespace daocode{
class LogFile{
public:
    LogFile();
    ~LogFile();
    int open();
    void close();
    void Write(const char*data,int len);
private:
    void rotate();
private:
    FILE *fp_;
    int total_;//当前文件大小
    int rotate_size_;
    std::string filename_;
};
}
#endif // LOGFILE_H
