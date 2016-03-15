#include <iostream>
#include "../net/EPoll.h"
#include "../net/Acceptor.h"
#include "../net/InetAddr.h"
#include "../net/EventLoop.h"
#include "../base/typedef.h"
using namespace std;


// g++ main.cpp ../net/Acceptor.cpp ../net/Channel.cpp ../net/EPoll.cpp ../net/EventLoop.cpp  -I../base -I. -I../net/  --std=c++11 -g

int main()
{
    cout << "Hello world!" << endl;
	
	InetAddr listenAddr;
	listenAddr.set_ip("127.0.0.1");
	listenAddr.set_port(9000);
	bool reuseport=true;
	Acceptor acceptor(listenAddr,reuseport);
	
	EventLoop loop(1000);
	ChannelPtr channel(new Channel(&loop,acceptor.get_fd()));//属于loop 1:n
	channel->enableReading();
	channel->setEventCallback(std::bind(&Acceptor::handleAccept,std::ref(acceptor)));	

	loop.addChannel(channel);
	loop.runInloop(std::bind(&Acceptor::listen,std::ref(acceptor),100));// listenc出
	loop.loop();
    return 0;
}
