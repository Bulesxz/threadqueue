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

	void listen(int max_con)
	{
		 sock.listen(max_con);
	}
	int get_fd(){
		return sock.get_fd();
	}
	int handleRead(); 
	private:
		SocketOpt sock;
};
#endif
