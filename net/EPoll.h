#ifndef EPOLL_H
#define EPOLL_H
#include <sys/epoll.h>
#include <vector>
#include <strings.h>

#include "../base/typedef.h"
#include "Channel.h"
typedef std::shared_ptr<Channel> ChannelPtr;
typedef std::vector<ChannelPtr> ChannelList;

class EPoll{
public:
	EPoll():epollfd_(::epoll_create1(EPOLL_CLOEXEC)){}
	~EPoll(){::close(epollfd_);}
	Timestamp poll(int timeoutMs, ChannelList* activeChannels);
	void fillActiveChannels(int numEvents,ChannelList* activeChannels);
	int  update(int operation,ChannelPtr& channel);

	int remove(ChannelPtr & channel){return update(EPOLL_CTL_DEL,channel);}

	int add(ChannelPtr & channel){return  update(EPOLL_CTL_ADD,channel);}

	int modify(ChannelPtr & channel){return update(EPOLL_CTL_MOD,channel);}

private:
	int epollfd_;
	std::vector<struct epoll_event> events_; 
};
#endif
