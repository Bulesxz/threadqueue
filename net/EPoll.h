#ifndef EPOLL_H
#define EPOLL_H
#include <sys/epoll.h>
#include <vector>
#include <../base/typedef.h>
#include "channel.h"
typedef std::vector<std::shared_ptr<Channel> > ChannelList;
typedef std::shared_ptr<Channel> ChannelPtr;
class EPoll{
public:
	EPoll():epollfd_(::epoll_create1(EPOLL_CLOEXEC)){}
	~EPoll(){::close(epollfd_);}
	Timestamp poll(int timeoutMs, ChannelList& activeChannels);
	void fillActiveChannels(int numEvents,ChannelList& activeChannels);
	int  update(int operation, Channel* channel);
	int remove(Channel* channel);
	int add(Channel* channel);
	int modify(Channel* channel);
private:
	int epollfd_;
	std::vector<struct epoll_event> events_; 
};
#endif
