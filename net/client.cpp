#include "InetAddr.h"
#include "socketopt.h"
#include <signal.h>
#include <stdio.h>
int  main()
{
	signal(SIGPIPE, SIG_IGN);

	std::string ip = "127.0.0.1";
	unsigned short port=10000;
	SocketOpt opt;
	int  ret = opt.createTcp();
	if (ret < 0){
                printf("%s \n",strerror(-ret));
        }
	ret = opt.connect(ip,port);
        if (ret < 0 ){
                printf("%s \n",strerror(-ret));
        }
	
	char buf[128]={0};
	ret = opt.read(buf,128);
	if (ret < 0){
		printf("%s \n",strerror(-ret));
	}
	printf("%s %d\n",buf,ret);
	

/*
        std::string msg="hello";
        ret = opt.write(msg.c_str(),msg.length());
        if (ret < 0){
                printf("%s \n",strerror(-ret));
        }
*/
	return 0;
}
