#include "EPoll.h"

Timestamp EPoll::poll(int timeoutMs, ChannelList& activeChannels)
{
  int numEvents = ::epoll_wait(epollfd_,
                               &*events_.begin(),
                               static_cast<int>(events_.size()),
                               timeoutMs);
  int savedErrno = errno;
  Timestamp now(Timestamp::Now());
  if (numEvents > 0)
  {
    fillActiveChannels(numEvents, activeChannels);
  }
  else if (numEvents == 0)
  {
    LOG_TRACE << "nothing happended";
  }
  else
  {
    // error happens, log uncommon ones
    if (savedErrno != EINTR)//非timeout
    {
      errno = savedErrno;
      LOG_SYSERR << "EPollPoller::poll()";
    }
  }
  return now;
}

void EPoll::fillActiveChannels(int numEvents,ChannelList& activeChannels)
{
	
  assert(static_cast<size_t>(numEvents) <= events_.size());//不可能大于监听数
  for (int i = 0; i < numEvents; ++i)
  {
    Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
    channel->set_revents(events_[i].events);//事件标志
    activeChannels.push_back(channel);
  }
}

int  EPoll::update(int operation, ChannelPtr channel)
{
  struct epoll_event event;
  bzero(&event, sizeof event);
  event.events = channel->events();//要监听的事件，读，写等
  event.data.ptr = channel;//这样写返回时，直接获取channel,
  if (::epoll_ctl(epollfd_, operation,channel->fd(), &event) < 0)//EPOLL_CTL_ADD, EPOLL_CTL_MOD,EPOLL_CTL_DEL
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

int EPoll::remove(ChannelPtr channel)
{
	return update(EPOLL_CTL_DEL,channel);
}

int EPoll::add(ChannelPtr channel)
{
	return	update(EPOLL_CTL_ADD,channel);
}

int  EPoll::modify(ChannelPtr channel)
{
	return update(EPOLL_CTL_MOD,channel);
}
