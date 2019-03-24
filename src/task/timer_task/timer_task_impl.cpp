#include "timer_task_impl.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <errno.h>
#include <cstring>
#include "x/task/thread_pool.h"
#include "timerfd.h"

#define MAX_EPOLL_EVENTS_NUM 8
#include <system_error>
namespace x{namespace task {

TimerTaskImpl::TimerTaskImpl()
{
    efd_ = 0;
    running_ = false;
    tp_ = nullptr;
    callback_ = nullptr;
    callback_param_ = nullptr;
}

TimerTaskImpl::~TimerTaskImpl()
{
    if (tp_)
    {
        x::task::ThreadPool::Destroy(tp_);
    }
    if (efd_)
    {
        close(efd_);
        efd_ = -1;
    }
    for (int fd : tfds_)
    {
        close(fd);
    }
    tfds_.clear();
}

bool TimerTaskImpl::Init()
{
    efd_ = epoll_create1(0);
    if (efd_ <= 0)
    {
        //todo: 错误处理
        return false;
    }

    running_ = true;
    epoll_thread_ = std::thread(&TimerTaskImpl::epollThread, this);

    return true;
}

void TimerTaskImpl::SetTask(void(*func)(void*), void* param)
{
    callback_ = func;
    callback_param_ = param;
}

void TimerTaskImpl::SetBackgroundTask(int thread_pool_size, int max_task_num)
{
    if (thread_pool_size >= 0)
    {
        tp_ = x::task::ThreadPool::Create();
        tp_->SetPoolSize(thread_pool_size);
        tp_->SetMaxTaskNum(max_task_num);
        tp_->SetThreadFunc(callback_);
        tp_->Start();
    }
}

int TimerTaskImpl::RunAt(int sec, int nsec)
{
    return 0;
}

int TimerTaskImpl::RunAfter(int sec, int nsec)
{
    return 0;
}

int TimerTaskImpl::RepeatAt(int sec, int nsec, int intval_sec, int interval_nsec)
{
    return 0;
}

int TimerTaskImpl::RepeatAfter(int sec, int nsec, int interval_sec, int interval_nsec)
{
    if ((sec == 0) && (nsec == 0))
    {
        nsec = 1;
    }
    TimerFd tfd;
    tfd.Create(sec, nsec, interval_sec, interval_nsec);

    epoll_event* event = new epoll_event;
    memset(event, 0, sizeof(epoll_event));
    event->data.fd = tfd.Fd();
    //event->data.ptr = callback_param_;
    event->events = EPOLLIN;
    int fd1 = event->data.fd;
    int fd2 = tfd.Fd();
    int fd3 = tfd.Move();
    printf("fd1:%d, fd2:%d, fd3:%d\n", fd1, fd2, fd3);

    int ret = 0;
    ret = epoll_ctl(
        efd_,
        EPOLL_CTL_ADD,
        tfd.Fd(),
        event
    );
    if (ret)
    {
        //todo: 出错处理
        return false;
    }
    int fd = tfd.Move();
    tfds_.insert(fd);

    itimerspec its;
    timerfd_gettime(fd, &its);
    printf("sec:%ld, nsec:%ld, intsec:%ld, intnsec:%ld, fd:%d\n", its.it_value.tv_sec, its.it_value.tv_nsec, its.it_interval.tv_sec, its.it_interval.tv_nsec, event->data.fd);
    return fd;
}

void TimerTaskImpl::epollThread()
{
    int fdsz = 0;
    int rdsz = 0;
    uint64_t data;
    epoll_event events[MAX_EPOLL_EVENTS_NUM];
    while (running_)
    {
        memset(events, 0, sizeof(epoll_event) * MAX_EPOLL_EVENTS_NUM);
        fdsz = epoll_wait(
            efd_,
            events,
            MAX_EPOLL_EVENTS_NUM,
            1000
        );
        for (int i = 0; i < fdsz; i++)
        {
            if (events[i].events & EPOLLIN)
            {
                rdsz = read(events[i].data.fd, &data, sizeof(data));
                printf("lxdebug, fd:%d, ptr:%p, u32:%d, u64:%lu, events:%d\n",
                    events[i].data.fd, events[i].data.ptr, events[i].data.u32, events[i].data.u64,
                    events[i].events);
                if (rdsz < 0)
                {
                    //todo: 错误处理
                }
                std::error_code ec = std::make_error_code((std::errc)errno);
                printf("data:%lu, fdsz:%d, rdsz:%d, fd:%d, errno:%d, msg:%s\n", data, fdsz, rdsz, events[i].data.fd, errno, ec.message().c_str());
                if (tp_)
                {
                    tp_->Add(events[i].data.ptr);
                }
                else
                {
                    callback_(events[i].data.ptr);
                }
            }
        }
    }
}

}}
