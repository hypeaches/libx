#include "timer_task_impl.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <cerrno>
#include <cstring>
#include "timer_impl.h"
#include "src/error/system_error_info.h"

namespace x{namespace task {

TimerTaskImpl::TimerTaskImpl(x::task::TimerImpl* timer)
{
    tfd_ = -1;
    expire_count_ = 0;
    timer_ = timer;
    func_ = nullptr;
    obj_ = nullptr;

    sec_ = 0;
    nsec_ = 0;
    interval_sec_ = 0;
    interval_nsec_ = 0;
    is_abs_time_ = false;
}

TimerTaskImpl::~TimerTaskImpl()
{
    if (tfd_ > 0)
    {
        int ret = epoll_ctl(timer_->Fd(), EPOLL_CTL_DEL, tfd_, NULL);
        if (ret)
        {
            //todo: epoll删除timerfd失败
        }
        else
        {
            tfd_ = -1;
            timer_ = nullptr;
        }
        close(tfd_);
    }
}

void TimerTaskImpl::Destroy()
{
    timer_->DestroyTask(this);
}

x::ErrorInfo TimerTaskImpl::Init()
{
    tfd_ = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC);
    if (tfd_ < 0)
    {
        return x::ErrorInfo(new x::SystemErrorInfo(errno, "create timer fd failed"));
    }
    return x::ErrorInfo();
}

x::task::TimerTask* TimerTaskImpl::SetTaskFunc(bool(*func)(int, void*), void* obj)
{
    func_ = func;
    obj_ = obj;
    return this;
}

x::task::TimerTask* TimerTaskImpl::At(int sec, int nsec)
{
    sec_ = sec;
    nsec_ = nsec;
    is_abs_time_ = true;
    return this;
}

x::task::TimerTask* TimerTaskImpl::After(int sec, int nsec)
{
    sec_ = sec;
    nsec_ = nsec;
    is_abs_time_ = false;
    return this;
}

x::task::TimerTask* TimerTaskImpl::Repeat(int sec, int nsec)
{
    interval_sec_ = sec;
    interval_nsec_ = nsec;
    return this;
}

x::ErrorInfo TimerTaskImpl::Run()
{
    itimerspec its;
    its.it_value.tv_sec = sec_;
    its.it_value.tv_nsec = nsec_;
    its.it_interval.tv_sec = interval_sec_;
    its.it_interval.tv_nsec = interval_nsec_;
    int flag = is_abs_time_ ? TFD_TIMER_ABSTIME : 0;

    int ret = timerfd_settime(tfd_, flag, &its, NULL);
    if (ret)
    {
        return x::ErrorInfo(new x::SystemErrorInfo(errno, "set timer failed"));
    }

    epoll_event event;
    memset(&event, 0, sizeof(event));
    event.data.ptr = this;
    event.events = EPOLLIN;
    ret = epoll_ctl(timer_->Fd(), EPOLL_CTL_ADD, tfd_, &event);
    if (ret)
    {
        return x::ErrorInfo(new x::SystemErrorInfo(errno, "epoll ctl failed"));
    }
    return x::ErrorInfo();
}

bool TimerTaskImpl::RunCallbackFunc()
{
    bool ret = false;
    if (func_)
    {
        ret = (*func_)(expire_count_, obj_);
    }
    return ret;
}

int TimerTaskImpl::Fd()
{
    return tfd_;
}

void TimerTaskImpl::SetExpireCount(int expire_count)
{
    expire_count_ = expire_count;
}

}}
