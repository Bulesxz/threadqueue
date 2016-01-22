#ifndef LOGFILE_H
#define LOGFILE_H
#include<stdio.h>
#include <string>
namespace daocode{
class LogFile{
public:
    LogFile(std::string filename,int rotate_size=1024*1024*5);
    ~LogFile();
    int open();
    void close();
    void Write(const char*data,int len);
    void setFilename(std::string filename);
    void setRotateSize(int rotate_size);
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
