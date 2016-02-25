#include "EPoll.h"

EPoll::EPoll():epollfd_(::epoll_create1(EPOLL_CLOEXEC)),events_(kInitEventListSize)
{
	std::cout<<"epollfd_"<<epollfd_<<std::endl;
}

Timestamp EPoll::poll(int timeoutMs, ChannelList* activeChannels)
{
	std::cout<<"poll "<<epollfd_<<" "<<events_.size()<<std::endl;
  int numEvents = ::epoll_wait(epollfd_,
                               &events_[0],
                               static_cast<int>(events_.size()),
                               timeoutMs);
  Timestamp now = Now();
  int savedErrno = errno;
  if (numEvents > 0)
  {
    fillActiveChannels(numEvents, activeChannels,now);
  }
  else if (numEvents == 0)
  {
    std::cout<<"nothing happended";
  }
  else
  {
    // error happens, log uncommon ones
    if (savedErrno != EINTR)//非timeout
    {
      errno = savedErrno;
	  std::cout <<"EPoll::poll" <<strerror(errno)<<std::endl;
    }
  }
  return now;
}

void EPoll::fillActiveChannels(int numEvents,ChannelList * activeChannels,Timestamp now)
{
	
 std::cout<<"EPoll::fillActiveChannels "<<numEvents<<"\n";
  assert(static_cast<size_t>(numEvents) <= events_.size());//不可能大于监听数
  for (int i = 0; i < numEvents; ++i)
  {
    Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
    channel->set_revents(events_[i].events);//事件标志
    activeChannels->push_back(channel); //应用计数问题
	//reinterpret_cast<Channel*>(events_[i].data.ptr)->handleEvent(now);//执行事件的回调函数
  }
}

int  EPoll::update(int operation, const ChannelPtr& channel)
{

	for(ChannelMap::iterator it=channelMap_.begin();it!=channelMap_.end();it++){
		std::cout<<"it :"<<it->first<<"\n";
	
	}	
  ChannelMap::iterator it = channelMap_.find(channel->get_fd());
  if (it == channelMap_.end()) 
  {
		std::cout<<"no find\n";
		return -2;
	}
  channelMap_[channel->get_fd()] = channel;
  struct epoll_event event;
  bzero(&event, sizeof event);
  event.events = channel->get_events();//要监听的事件，读，写等
  event.data.ptr =  static_cast<void*>( channel.get());//这样写返回时，直接获取channel,
  if (::epoll_ctl(epollfd_, operation,channel->get_fd(), &event) < 0)//EPOLL_CTL_ADD, EPOLL_CTL_MOD,EPOLL_CTL_DEL
  {
	
	std::cout<<epollfd_<<":"<<channel->get_fd()<<std::endl;
	std::cout<<"epoll_ctl error \n";
	std::cout<<strerror(errno)<<std::endl;
	exit(0);
    if (operation == EPOLL_CTL_DEL)
    {
    	;
    }
    else
    {
  	;
    }
    return 1;
  }
  return 0;
}



