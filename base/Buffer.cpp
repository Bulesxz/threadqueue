#include "Buffer.h"

#include<iostream>
using namespace daocode;
void Buffer::append(const char* data,int len)//写入
{

        buffer_[write_index].append(data,len);
}

 void Buffer::append(const std::string& data)
{
         buffer_[write_index].append(data);
}

 int Buffer::readableBytes()//可读的字节
{
    std::cout<<std::endl;
        return buffer_[read_index].size() - seek_;
}
 const char* Buffer::GetPeek()
{
        return buffer_[read_index].data() + seek_;
}

 void Buffer::changeIndex()
{
    std::swap(read_index,write_index);
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
    buffer_[read_index].clear();
}

const std::string & Buffer::writeBuffRef()
{
    return   buffer_[write_index];
}
