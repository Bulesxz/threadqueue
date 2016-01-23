#ifndef BUFFER_H
#define BUFFER_H
#include <string>
namespace daocode{
class Buffer{
public:
        Buffer():seek_(0),read_index(0),write_index(1){}
         void append(const char* data,int len);//写入
         void append(const std::string& data);//写入
         int readableBytes();//可读的字节
         const char* GetPeek();
         void changeIndex();
         void  seek(int n);//读n个
         int GetSeek();
         void resetSeek();
         void clearReadbuf();
         const std::string & writeBuffRef();
private:
        std::string buffer_[2]; //0读1写
        int seek_;
        int read_index; //read false,wirte,true
        int write_index;

};
}
#endif
