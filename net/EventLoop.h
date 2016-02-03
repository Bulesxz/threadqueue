#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <thread>
#include <Mutex>
#include <vector>
#include <memory>
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
	private:
		bool is_start;
		EPoll poller;
		ChannelList activeChannels;
	 	std::vector<Callback> pendingFunctors_;
		std::Mutex mutex_;
		std::thread::id threadId_;
		int wakeupFd_;
		std::shared_ptr<Channel> wakeupChannel_; //不能被复制和赋值
};
#endif
