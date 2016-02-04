#include "Channel.h"
#include <poll.h>
#include "EventLoop.h"
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;


Channel::Channel(EventLoop *loop,int fd):loop_(loop),fd_(fd)
{
}
void Channel::handleEvent(Timestamp pollReturnTime_)
{
std::cout<<"handleEvent\n";	
}

void Channel::update()
{
  loop_->updateChannel(ChannelPtr(this));
}

