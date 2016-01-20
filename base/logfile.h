#ifndef LOGFILE_H
#define LOGFILE_H
#include<stdio.h>
class LogFile{
public:
    LogFile(int rotate_size);
    int open(const char * filename);
    void close();
private:
    void rotate();
private:
    FILE *fd_;
    int total_;//当前文件大小
    int rotate_size_;
};
#endif // LOGFILE_H
