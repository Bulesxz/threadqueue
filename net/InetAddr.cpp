#include <InetAddr.h>
#Include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


InetAddr::InetAddr(const std::string ip,int port)
{
    addr_.sin_family = AF_INET;
    addr_.port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip);
}
