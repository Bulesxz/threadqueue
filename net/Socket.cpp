#include <Socket.h>
#include <InetAddr.h>
using namespace daocode;

void Socket::bind(const InetAddress& addr )
{
    int ret =bind(fd_,
              struct sockaddr *name,
              int namelen);

}
