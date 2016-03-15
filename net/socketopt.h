#ifndef SOCKETOPT_H
#define	SOCKETOPT_H 
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "InetAddr.h"

/*
*如果有错误，返回值为错误码的相反数，-errno
*/
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
		socklen_t len=0;
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

	int set_reuseaddr( int option_value=true)
	{
		option_value=true;
		int ret = ::setsockopt(_socket_fd,SOL_SOCKET, SO_REUSEADDR,(const void *) &option_value,sizeof(option_value));
		return (ret < 0) ? (errno ? -errno : ret) : 0;
	}

	int set_reuseport( int option_value=true)
	{
		option_value=true;
		int ret = ::setsockopt(_socket_fd,SOL_SOCKET, SO_REUSEPORT,(const void *) &option_value,sizeof(option_value));
		return (ret < 0) ? (errno ? -errno : ret) : 0;
	}


	int setNonBlockAndCloseOnExec()
	{
		//set-nonblock
		int flags = ::fcntl(_socket_fd, F_GETFL, 0);
		flags |= O_NONBLOCK;
		int ret = ::fcntl(_socket_fd, F_SETFL, flags);
		// close-on-exec
		flags = ::fcntl(_socket_fd, F_GETFD, 0);
		flags |= FD_CLOEXEC;
		ret = ::fcntl(_socket_fd, F_SETFD, flags);
		return ret;
	}

	int setKeepAlive(bool on)
	{
		int optval = on ? 1 : 0;
		errno =0;
		int ret = ::setsockopt(_socket_fd, SOL_SOCKET, SO_KEEPALIVE,&optval, sizeof(optval));
		return (ret < 0) ? (errno ? -errno : ret) : 0;
	}

	int getError() const
	{
		int optval;
		socklen_t optlen = static_cast<socklen_t>(sizeof optval);
		int ret = ::getsockopt(_socket_fd, SOL_SOCKET, SO_ERROR, &optval, &optlen);
		return (ret < 0) ? (errno ? -errno : ret) : ret;
	}

	struct sockaddr_in getAddr() const
	{
		struct sockaddr_in localaddr;
		bzero(&localaddr, sizeof localaddr);
		socklen_t addrlen = static_cast<socklen_t>(sizeof localaddr);
		int ret = ::getsockname(_socket_fd, (struct sockaddr*)(&localaddr), &addrlen);
		if (ret < 0)
		{
			printf("sockets::getLocalAddr\n");
		}
		return localaddr;
	}


	struct sockaddr_in getPeerAddr() const
	{
		struct sockaddr_in peeraddr;
		bzero(&peeraddr, sizeof peeraddr);
		socklen_t addrlen = static_cast<socklen_t>(sizeof peeraddr);
		if (::getpeername(_socket_fd, (struct sockaddr*)(&peeraddr), &addrlen) < 0)
		{
			printf("sockets::getPeerAddr\n");
		}
		return peeraddr;
	}

	void close() //主动关闭的话会停留在TIME_WAIT 几分钟 ，这时再打开，会出现  Address already in use 
        {
            if (!isInvalid ())
            {
                //::shutdown(_socket_fd, SHUT_RDWR);
                ::close(_socket_fd);
		_socket_fd=INVALID;
            }
        }

	int get_fd()
	{
		return _socket_fd;
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
