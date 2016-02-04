#include "Channel.h"
Channel::Channel(EventLoop *loop,int fd):loop_(loop),fd_(fd)
{
}
void Channel::handleEvent(Timestamp pollReturnTime_)
{
	
}
