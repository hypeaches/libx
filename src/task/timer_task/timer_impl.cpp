#include "timer_impl.h"
#include <sys/epoll.h>
#include <cerrno>

namespace x{namespace task{

TimerImpl::TimerImpl()
{
    efd_ = -1;
    running_ = false;
    tp_ = nullptr;
}

TimerImpl::~TimerImpl()
{

}

x::task::TimerTask* TimerImpl::CreateTask()
{

}

int TimerImpl::Init()
{
    efd_ = epoll_create1(0);
    if (efd_ == -1)
    {
        return errno;
    }
    running_ = true;
    epoll_thread_ = std::thread(&TimerImpl::epollThread, this);
}

void TimerImpl::CreateThreadPool(int thread_pool_size, int max_task_num)
{

}

void TimerImpl::epollThread()
{
    int fdsz = 0;
    const int max_events_count = 8;
    epoll_event events[max_events_count];
    while (running_)
    {
        
    }
}

}}