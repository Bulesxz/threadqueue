#include "EventLoop.h"

int createEventfd()
{
  int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
	assert(evtfd >=0 )
  return evtfd;
}

EventLoop::EventLoop(int timeoutMs):
	timeoutMs_(timeoutMs),threadId_(std::this_thread::get_id()),
	wakeupFd_(createEventfd())/*唤醒poller用*/,
	wakeupChannel_(new Channel(this,wakeupFd_))
{
	wakeupChannel_.setReadCallback(std::bind(&EventLoop::wakeupRead,this));
	poller_.add(wakeupChannel_);
}

void EventLoop::loop()
{
	is_start = true;
	while(is_start)
	{
		activeChannels_.clear();
		Timestamp time = poller_.poll(timeoutMs_,activeChannels_);
		for (size_t i=0;i < activeChannels_.size();i++){
			activeChannels_[i].handleEvent(pollReturnTime_);
		}
		DoPendingFunctor();
	}
}

void EventLoop::runInloop(Callback& cb)
{
	if (isInLoopThread())
	{
		cb();
	}
	
	{
		std::lock_guard lock(mutex_);
		pendingFunctors_.push_back();
	}
	
	wakeup();
}

void EventLoop::DoPendingFunctor()
{
	std::vector<Callback> functors;
	{
  		std::lock_guard lock(mutex_);
		functors.swap(pendingFunctors_);
	}
	for (size_t i = 0; i < functors.size(); ++i)
	{
    	functors[i]();
  	}
}


void EventLoop::wakeup()
{
  uint64_t one = 1;
  ssize_t n = sockets::write(wakeupFd_, &one, sizeof one);
  if (n != sizeof one)
  {
    std::cout << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
  }
}

void EventLoop::wakeupRead()
{
  uint64_t one = 1;
  ssize_t n = sockets::read(wakeupFd_, &one, sizeof one);
  if (n != sizeof one)
  {
    std::cout << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
  }
}

