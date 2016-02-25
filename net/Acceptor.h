#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include "InetAddr.h"
#include "socketopt.h"
#include <../base/typedef.h>
class Acceptor{
public:
	typedef  std::function<void(int sockfd, const InetAddr&)> NewConnectionCallback;
	Acceptor(InetAddr& listenAddr, bool reuseport);
	~Acceptor(){
		std::cout<<"~Acceptor\n";
		sock.close();
	}

	void listen(int max_con)
	{
		 sock.listen(max_con);
	}
	int get_fd(){
		return sock.get_fd();
	}

	void setCallback(const NewConnectionCallback& c)
    {
        newConnectionCallback_ = c;
    }

	int handleAccept();
	private:
		SocketOpt sock;
		NewConnectionCallback newConnectionCallback_;
};
#endif
