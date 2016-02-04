#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <../base/typedef.h>
#include "EPoll.h"
#include "Channel.h"
class EventLoop{
	public:
		EventLoop(int timeoutMs);
		void loop();
		inline bool isInLoopThread()
		{
			if (threadId_==std::this_thread::get_id())
				return true;
			else
				return false;
		}
		void updateChannel(const ChannelPtr& channel);
		void addChannel(const ChannelPtr& channel);
		void runInloop(const Callback& cb);
		void DoPendingFunctor();
		void wakeup();
		void wakeupRead();
	private:
		bool is_start;
		EPoll poller_;
		ChannelList activeChannels_;
	 	std::vector<Callback> pendingFunctors_;
		std::mutex mutex_;
		std::thread::id threadId_;
		int wakeupFd_;
		ChannelPtr wakeupChannel_;
		int timeoutMs_;
};
#endif
