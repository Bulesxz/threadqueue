#ifndef SOCKET_H
#define SOCKET_H

namespace daocode{
public Socket{
public :
    Socket(int sockfd):sockfd_(sockfd){}
    ~Socket();
    void bind(const InetAddress& localaddr);
    void listen();
    void accpet();
    const int sockfd_;
};
}
#endif // SOCKET_H
