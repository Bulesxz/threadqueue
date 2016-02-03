#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include "InetAddr.h"
#include "socketopt.h"
class Acceptor{
public:
	Acceptor(InetAddr& listenAddr, bool reuseport);
	~Acceptor(){
		sock.close();
	}

	int listen(int max_con)
	{
		 return sock.listen(max_con);
	}
	int get_fd(){
		return sock.get_fd();
	}
	int handleRead(); 
	private:
		SocketOpt sock;
};
#endif
