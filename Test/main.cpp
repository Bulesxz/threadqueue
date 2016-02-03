#include <iostream>
#include "../net/EPoll.h"
#include "../net/Acceptor.h"
#include "../net/InetAddr.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
	
	InetAddr listenAddr;
	listenAddr.set_ip("127.0.0.1");
	listenAddr.set_port(9000);
	bool reuseport=true;
	Acceptor acceptor(listenAddr,reuseport);
	acceptor.listen(100);	
	
	EventLoop loop;
	Channel channel(&loop,acceptor.get_fd());
	EPoll poll;
	poll.add(&channel);
	
	loop.loop();
    return 0;
}
