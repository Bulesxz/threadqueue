#include "logfile.h"
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <logger.h>
#include <iostream>
using namespace daocode;
LogFile::LogFile(std::string filename,int rotate_size):fp_(NULL),total_(0),rotate_size_(rotate_size),filename_(filename)
{
}

LogFile::~LogFile()
{
    std::cout<<"LogFile::~LogFile\n";
    close();
}
int LogFile::open()
{
    if (filename_.empty() || rotate_size_ <=0){
        return 1;
    }
    FILE* fd = fopen(filename_.c_str(),"a");
    if (fd==NULL){
         LOG_ERROR("error=%s\n", strerror(errno));
         return 1;
    }
    fp_ = fd;

    struct stat st;
    //int ret = fstat(fp_->_file,&st);
	int ret = fstat(fileno(fp_),&st);

    if(ret == -1)
    {
        LOG_ERROR("error=%s\n", strerror(errno));
        return 1;
    }
    total_ = st.st_size;
    return 0;
}

void LogFile::close()
{
    if (fp_ != NULL)
    {
        fflush(fp_);
        fclose(fp_);
    }
}

void LogFile::Write(const char*data,int len)
{
    std::cout<<"LogFile::Write\n";
    int len_ = fwrite(data,len,1,fp_);
    if (len_<=0){
        LOG_ERROR("error=%s\n", strerror(errno));
        return ;
    }
    //if (len>=4096)
        fflush(fp_);
    total_ += len_;
    if (rotate_size_ >0 && total_ >= rotate_size_){
        rotate();
    }
}

void LogFile::rotate()
{
    close();
    char newpath[64];
    time_t time;
    struct timeval tv;
    struct tm *tm;
    gettimeofday(&tv, NULL);
    time = tv.tv_sec;
    tm = localtime(&time);
    sprintf(newpath, "%s.%04d%02d%02d-%02d%02d%02d",
            filename_.c_str(),
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec);

    //printf("rename %s => %s\n", this->filename, newpath);
    int ret = rename(filename_.c_str(), newpath);
    if (ret==-1){
         LOG_ERROR("error=%s\n", strerror(errno));
         return ;
    }

    open();
}

void LogFile::setFilename(std::string filename)
{
    filename_ = filename;
}
void LogFile::setRotateSize(int rotate_size)
{
    rotate_size_= rotate_size;
}
