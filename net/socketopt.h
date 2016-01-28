#ifndef SOCKETOPT_H
#define	SOCKETOPT_H 
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "InetAddr.h"

class SocketOpt{
public :
	#define INVALID -1
	SocketOpt(){ _socket_fd=INVALID;}
	SocketOpt(int fd):_socket_fd(fd){}
	int createTcp()
	{
		errno=0;
		if (!isInvalid ())
			close();

		int ret = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ret < 0){
			return errno ? -errno : ret;//返回错误码
		}else{
			_socket_fd = ret;
			return ret;
		}
	}
	int bindTcp(const std::string &server_address,   unsigned short port)
	{
		InetAddr addr;
		addr.set_ip(server_address);
		addr.set_port(port);
		errno = 0; 
		int ret = ::bind(_socket_fd, addr.addr(), sizeof(*(addr.addr())) );
		if (ret < 0) {
			return errno ? -errno : ret;
		}
		return 0;
	}

	int bindAnyTcp(unsigned short port)
	{
		InetAddr addr;
		addr.set_anyip();
		addr.set_port(port);
		errno = 0;
		int ret = ::bind(_socket_fd, addr.addr(), sizeof(*(addr.addr())) );
                if (ret < 0) {
                        return errno ? -errno : ret;
                }
		return 0;
	}
	
	int listen(int max_con)
	{
    		errno = 0;
            	int ret = ::listen(_socket_fd, max_con);
		if (ret < 0) {
                        return errno ? -errno : ret;
                }
                return 0;
	}

	
	int accept(InetAddr *addr)
	{
		errno = 0;
		//int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
		socklen_t len;
		int ret = ::accept(_socket_fd,addr->addr(),&len);
		if (ret < 0) {
                        return errno ? -errno : ret;
                }
		
                return ret;
	}

	int connect(const std::string &ip,unsigned short port) 
	{
		InetAddr addr;
		addr.set_port(port);
		addr.set_ip(ip);
		errno = 0;
		int ret = ::connect(_socket_fd, addr.addr(), sizeof(*addr.addr()));
		if (ret < 0) {
			return 	errno ? -errno : ret;
		}
		return 0;
	}
	
	ssize_t read(void *buf, size_t count)
	{
		errno = 0;
  		ssize_t size =  ::read(_socket_fd, buf, count);
		if (size < 0) {
                        return  errno ? -errno : size;
                }
		return size;
	}
	ssize_t write(const void *buf, size_t count)
	{
  		ssize_t size =  ::write(_socket_fd, buf, count);
		if (size < 0) {
                        return  errno ? -errno : size;
                }
                return size;
	}

	void close()
        {
            if (!isInvalid ())
            {
                //::shutdown(_socket_fd, SHUT_RDWR);
                ::close(_socket_fd);
		_socket_fd=INVALID;
            }
        }

private:
	bool isInvalid(){
		if (_socket_fd==INVALID)
			return true;
		else
			return false;
	}
private:
	int _socket_fd ;
};
#endif
