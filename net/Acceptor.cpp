#include "Acceptor.h"
#include <iostream>
Acceptor::Acceptor(InetAddr& listenAddr, bool reuseport)
{

		int fd = sock.createTcp();
		if (fd < 0){
				return ;
		}
	
		sock.setNonBlockAndCloseOnExec();

		int ret = sock.bindTcp(listenAddr.get_ip(),listenAddr.get_port());
		if (ret<0)
		{
				std::cout<<"-------------\n";
				return ;
		}
		sock.set_reuseaddr(true);
		sock.set_reuseport(reuseport);
}
int Acceptor::handleAccept()
{
	InetAddr peerAddr;
  	int connfd = sock.accept(&peerAddr);

	if (connfd >= 0)
    {
        if (newConnectionCallback_) newConnectionCallback_(connfd, peerAddr);
        else ::close(connfd);
    }
	if (connfd < 0){
		return connfd;
	}
	
	std::cout<<"iiiiiiiiiiiiiii\n";
	return 0;
}

