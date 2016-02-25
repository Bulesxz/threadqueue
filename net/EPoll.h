#ifndef EPOLL_H
#define EPOLL_H
#include <sys/epoll.h>
#include <vector>
#include <strings.h>
#include <map>
#include "../base/typedef.h"
#include "Channel.h"
typedef std::shared_ptr<Channel> ChannelPtr;
typedef std::vector<Channel*> ChannelList;

class EPoll{
public:
	EPoll();
	~EPoll(){ std::cout<<"~EPoll\n";::close(epollfd_);}
	Timestamp poll(int timeoutMs, ChannelList* activeChannels);
	void fillActiveChannels(int numEvents,ChannelList* activeChannels,Timestamp now);
	int  update(int operation,const ChannelPtr& channel);

	int remove(const ChannelPtr & channel){
				channelMap_.erase(channel->get_fd());
				return update(EPOLL_CTL_DEL,channel);}

	int add(const ChannelPtr & channel){
				std::cout<<"EPoll::add:"<<channel->get_fd()<<"\n"; 
				channelMap_[channel->get_fd()] = channel;
				return  update(EPOLL_CTL_ADD,channel);}

	int modify(const ChannelPtr & channel){
			std::cout<<"EPoll::modify:"<<channel->get_fd()<<"\n";
		 /*channelMap_[channel->get_fd()] = channel;*/return update(EPOLL_CTL_MOD,channel);}

private:
	int epollfd_;
	std::vector<struct epoll_event> events_;
  	typedef std::map<int, ChannelPtr> ChannelMap;
    ChannelMap channelMap_;
	static const int kInitEventListSize = 16; 
};
#endif
