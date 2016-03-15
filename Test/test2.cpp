#include "InetAddr.h"
#include "socketopt.h"
#include <signal.h>
#include <stdio.h>
int  main()
{
	signal(SIGPIPE, SIG_IGN);

	InetAddr addr;
	short f = addr.get_family();
	printf("%d %d \n",f,AF_INET);
	addr.set_port(10000);
	unsigned short port = addr.get_port();
	printf("%d \n",port);

	addr.set_ip("127.0.0.1");
	std::string ip = addr.get_ip();
	printf("%s \n",ip.c_str());

	SocketOpt opt;
	int fd = opt.createTcp();
	if (fd<0)
		printf("createTcp %s \n",strerror(-fd));
	printf("fd :%d \n",fd);
	

	//int ret = opt.bindTcp(ip,port);
	int ret = opt.bindAnyTcp(port);
	if (ret < 0 ){
		printf("bindAnyTcp %s \n",strerror(-ret));
	}


	ret = opt.listen(SOMAXCONN);	
	if (ret < 0 ){
                printf("listen %s \n",strerror(-ret));
        }
	
	InetAddr accept_addr;
	ret = opt.accept(&accept_addr);
        if (ret < 0 ){
                printf("accept %s \n",strerror(-ret));
		return 1;
        }

        printf("accept fd %d \n",ret);
	SocketOpt opt1(ret);
	std::string msg="hello";
	ret = opt1.write(msg.c_str(),msg.length());
	if (ret < 0){
		printf("write %s \n",strerror(-ret));
	}

/*	
	char buf[128]={0};
	ret = opt.read(buf,128);
	if (ret < 0){
		printf("%s \n",strerror(-ret));
	}
	printf("%s %d\n",buf,ret);
	
*/	return 0;
}
