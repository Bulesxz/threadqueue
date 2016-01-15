#ifndef NONABLECOPY_H
#define NONABLECOPY_H
namespace daocode{
class nonablecopy{
    protected:
        nonablecopy(){}
        ~nonablecopy(){}
    private:
        nonablecopy(const nonablecopy&);
        nonablecopy& operator=(const nonablecopy&);
};
}
#endif // NONABLECOPY_H
