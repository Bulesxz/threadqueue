#ifndef CHANNEL_H
#define CHANNEL_H
#include <../base/typedef.h>
#include <vector>
typedef std::function<void(Timestamp)>  ReadEventCallback;
typedef std::function<void(void)>  EventCallback ;
class EventLoop;
class Channel{
	public:
		Channel(EventLoop* loop, int fd);
  		~Channel(){};
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
		void  set_revents(const int revents)
		{
			revents_ = revents;
		}

		int get_events()
		{
			return events_;
		}
		int get_fd(){
			return fd_;
		}
		
		void update();
  		bool isNoneEvent() const { return events_ == kNoneEvent; }

  		void enableReading() { events_ |= kReadEvent; update(); }
  		void disableReading() { events_ &= ~kReadEvent; update(); }
  		void enableWriting() { events_ |= kWriteEvent; update(); }
  		void disableWriting() { events_ &= ~kWriteEvent; update(); }
  		void disableAll() { events_ = kNoneEvent; update(); }
  		bool isWriting() const { return events_ & kWriteEvent; }
  		bool isReading() const { return events_ & kReadEvent; }

	private:
		static const int kNoneEvent;
		static const int kReadEvent;
		static const int kWriteEvent;

	private:
		EventLoop* loop_;
		int fd_;
		int revents_;
		int events_;//要监听的事件
		ReadEventCallback readCallback_;//不同事件对应这不同的回调函数
		EventCallback writeCallback_;
		EventCallback closeCallback_;
		EventCallback errorCallback_;
};

#endif

