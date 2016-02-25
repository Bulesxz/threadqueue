#include "Channel.h"
#include <poll.h>
#include "EventLoop.h"
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;


Channel::Channel(EventLoop *loop,int fd):loop_(loop),fd_(fd)
{
}
void Channel::handleEvent(Timestamp pollReturnTime_)
{
	std::cout<<"handleEvent fd:"<<get_fd()<<"\n";
	eventCallback_();	
}

void Channel::update()
{
  loop_->updateChannel(shared_from_this());
}

