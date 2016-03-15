#ifndef InetAddr_H
#define InetAddr_H
#include <string.h>
#include <arpa/inet.h>
#include <string>
class InetAddr{
public:
	InetAddr(){
		memset(&_addr, 0, sizeof(struct sockaddr_in));
		 _addr.sin_family = AF_INET;
	}

	InetAddr(const struct sockaddr_in &addr){
                memcpy(&_addr, &addr, sizeof(struct sockaddr_in));
        }

/*
	void set_family(short family){ 
		_addr.sin_family = family;
	}*/
	short get_family()
	{
		return _addr.sin_family;
	}
	void set_port (unsigned short port){
		_addr.sin_port = htons(port);
	}
	unsigned short get_port()
	{
		return ntohs(_addr.sin_port);
	}
	void set_ip (const std::string ip ){
		_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	}
	
	void set_anyip()
	{
		_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	
	std::string get_ip()
	{
		char buf[INET_ADDRSTRLEN];
            	const char* p = inet_ntop(AF_INET, &_addr.sin_addr.s_addr, buf, sizeof(buf));
            	return p ? p : std::string();
	}
	
	struct sockaddr * addr()
	{
		return (struct sockaddr*)(&_addr);
	}

	/*struct const sockaddr * sockaddr_cast(){
		return (struct const sockaddr*)(&_addr);
	}*/
private:
     struct sockaddr_in _addr;
	//socklen_t _len;
};
//ipv4
#endif
