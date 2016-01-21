#include "Buffer.h"
using namespace daocode;
void Buffer::append(const char* data,int len)//写入
{
        buffer_[!rw_index].append(data,len);
}

 void Buffer::append(const std::string& data)
{
         buffer_[!rw_index].append(data);
}

 int Buffer::readableBytes()//可读的字节
{
        return buffer_[rw_index].size() - seek_;
}
 const char* Buffer::GetPeek()
{
        return buffer_[rw_index].data() + seek_;
}

 void Buffer::changeIndex()
{
        rw_index = !rw_index;
}
 void Buffer::seek(int n)
{
        seek_ +=n;
}

 int Buffer::GetSeek()
{
        return seek_;
}
 void Buffer::resetSeek()
{
        seek_=0;
}

void Buffer::clearReadbuf()
{
    buffer_[rw_index].clear();
}

const std::string & Buffer::writeBuffRef()
{
    return   buffer_[!rw_index];
}
