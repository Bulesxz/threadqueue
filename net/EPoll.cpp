#include "EPoll.h"
Timestamp EPoll::poll(int timeoutMs, ChannelList* activeChannels)
{
	std::cout<<"log "<<epollfd_<<" "<<events_.size();
  int numEvents = ::epoll_wait(epollfd_,
                               &*events_.begin(),
                               static_cast<int>(events_.size()),
                               timeoutMs);
  int savedErrno = errno;
  Timestamp now = 0;//Now();
  if (numEvents > 0)
  {
    fillActiveChannels(numEvents, activeChannels);
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
     std::cout << "EPollPoller::poll()";
	  std::cout << strerror(errno);
    }
  }
  return now;
}

void EPoll::fillActiveChannels(int numEvents,ChannelList * activeChannels)
{
	
  assert(static_cast<size_t>(numEvents) <= events_.size());//不可能大于监听数
  for (int i = 0; i < numEvents; ++i)
  {
    Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
    channel->set_revents(events_[i].events);//事件标志
    activeChannels->push_back((ChannelPtr)channel);
  }
}

int  EPoll::update(int operation, const ChannelPtr& channel)
{
  struct epoll_event event;
  bzero(&event, sizeof event);
  event.events = channel->get_events();//要监听的事件，读，写等
  event.data.ptr = (void *)channel.get();//这样写返回时，直接获取channel,
  if (::epoll_ctl(epollfd_, operation,channel->get_fd(), &event) < 0)//EPOLL_CTL_ADD, EPOLL_CTL_MOD,EPOLL_CTL_DEL
  {
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



