#include "logfile.h"
#include <errno.h>
#include <string.h>
LogFile::LogFile(int rotate_size):fd_(-1),total(0),rotate_size_(1024*1024*5)
{
}
LogFile::~LogFile()
{
    close();
}
int LogFile::open(const char * filename)
{
    FILE* fd = fopen(filename,"a")
    if (fd==NULL){
         LOG_ERROR("error=%s\n", strerror(errno));
         return 1;
    }
    fd_ = fd;

    struct stat;
    int ret = fstat(fileno(fp_),&stat);
    if(ret == -1)
    {
        LOG_ERROR("error=%s\n", strerror(errno));
        return 1;
    }
    total_ = stat.st_size;
    return 0;
}

void LogFile::close()
{
    if (fp_ != NULL)
    {
        fclose(fp_);
    }
}

void LogFile::LogWrite(const char*data,int len)
{
    int len_ = fwrite(data,len,1,fp_)
}


