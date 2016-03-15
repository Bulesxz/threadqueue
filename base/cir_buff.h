#ifndef  CIR_BUFFER_H
#define  CIR_BUFFER_H
#include<atomic>
#include<vector>
template<typename T>
class cir_buffer{
public:
    cir_buffer(int size):index_(0),len_(size){
        buffer_.resize(len_);
    }
    void insert(const T &t){
        index_ = (++index_) % len_;
        buffer_[index_%len_]=t;
    }
    T& back(){
        return buffer_[index_%len_];
    }

    int begin(){
        return index_%len_;
    }
    int end(){
        return (index_+len_-1)%len_;
    }
private:
    std::vector<T> buffer_;
    std::atomic_int index_;
    int len_;
};
#endif // CIR_BUFFER_H
