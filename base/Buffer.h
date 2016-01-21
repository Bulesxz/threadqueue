#ifndef BUFFER_H
#define BUFFER_H
#include <string>
namespace daocode{
class Buffer{
public:
        Buffer():seek_(0),rw_index(false){}
         void append(const char* data,int len);//д��
         void append(const std::string& data);//д��
         int readableBytes();//�ɶ����ֽ�
         const char* GetPeek();
         void changeIndex();
         void  seek(int n);//��n��
         int GetSeek();
         void resetSeek();
         void clearReadbuf();
         const std::string & writeBuffRef();
private:
        std::string buffer_[2]; //0��1д
        int seek_;
        bool rw_index; //read false,wirte,true

};
}
#endif
