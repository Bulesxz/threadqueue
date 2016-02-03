#ifndef CHANNEL_H
#define CHANNEL_H
typedef std::function<void(Timestamp)>  ReadEventCallback;
typedef std::function<void(void)>  EventCallback ;
class EventLoop;
class Channel{
	public:
		Channel(EventLoop* loop, int fd);
  		~Channel();
		void handleEvent(Timestamp receiveTime);
		void setReadCallback(const ReadEventCallback& cb)//设置回调函数
		{ 
			readCallback_ = cb; 
		}
		
		void setWriteCallback(const EventCallback& cb)
		{ 
			writeCallback_ = cb; 
		}
		
		void setCloseCallback(const EventCallback& cb)
		{ 
			closeCallback_ = cb; 
		}
		
		void setErrorCallback(const EventCallback& cb)
		{ 
			errorCallback_ = cb; 
		}
	private:
		EventLoop* loop_;
		int fd_;
		int revents_;
		ReadEventCallback readCallback_;//不同事件对应这不同的回调函数
		EventCallback writeCallback_;
		EventCallback closeCallback_;
		EventCallback errorCallback_;
};
#endif

