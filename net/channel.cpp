#include "channel.h"
void Channel::update()
{
  addedToLoop_ = true;
  loop_->updateChannel(this);
}
void Channel::handleEvent(Timestamp pollReturnTime_)
{
	
}
