#ifndef INETADDR_H
#define INETADDR_H

#include <netinet/in.h>

namespace daocode{
class InetAddr{
    public:
        InetAddr(const std::string ip,int port);
    private:
        struct sockaddr_in addr_;
};
}
#endif // INNETADDR_H

