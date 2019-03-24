#include "timerfd.h"
#include <unistd.h>
#include <sys/timerfd.h>
#include <cstring>
#include <cstdio>
namespace x{namespace task{

TimerFd::TimerFd()
{
    fd_ = -1;
}

TimerFd::~TimerFd()
{
    if (fd_ != -1)
    {
        close(fd_);
        fd_ = -1;
    }
}

int TimerFd::Fd()
{
    return fd_;
}

int TimerFd::Move()
{
    int fd = fd_;
    fd_ = -1;
    return fd;
}

TimerFd& TimerFd::Create()
{
    fd_ = timerfd_create(
        CLOCK_REALTIME,
        TFD_NONBLOCK
    );
    if (fd_ == -1)
    {
        //todo: 错误处理
        return *this;
    }

    itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;

    int ret = 0;
    ret = timerfd_settime(
        fd_,
        0,
        &its,
        NULL
    );
    if (ret)
    {
        //todo: 错误处理
        return *this;
    }
    return *this;
}

TimerFd& TimerFd::SetTime(int sec, int nsec)
{
    int ret = 0;
    itimerspec its;
    
    ret = timerfd_gettime(
        fd_,
        &its
    );
    if (ret)
    {
        //todo: 错误处理
        return *this;
    }
printf("sec:%ld, nsec:%ld, intsec:%ld, intnsec:%ld\n", its.it_value.tv_sec, its.it_value.tv_nsec, its.it_interval.tv_sec, its.it_interval.tv_nsec);
    its.it_value.tv_sec = sec;
    its.it_value.tv_nsec = nsec;
printf("sec:%ld, nsec:%ld, intsec:%ld, intnsec:%ld\n", its.it_value.tv_sec, its.it_value.tv_nsec, its.it_interval.tv_sec, its.it_interval.tv_nsec);

    ret = timerfd_settime(
        fd_,
        0,
        &its,
        NULL
    );
    if (ret)
    {
        //todo: 错误处理
        return *this;
    }

    return *this;
}

TimerFd& TimerFd::SetRepeat(int sec, int nsec)
{
    int ret = 0;
    itimerspec its;
    
    ret = timerfd_gettime(
        fd_,
        &its
    );
    if (ret)
    {
        //todo: 错误处理
        return *this;
    }
printf("sec:%ld, nsec:%ld, intsec:%ld, intnsec:%ld\n", its.it_value.tv_sec, its.it_value.tv_nsec, its.it_interval.tv_sec, its.it_interval.tv_nsec);
    its.it_interval.tv_sec = sec;
    its.it_interval.tv_nsec = nsec;
printf("sec:%ld, nsec:%ld, intsec:%ld, intnsec:%ld\n", its.it_value.tv_sec, its.it_value.tv_nsec, its.it_interval.tv_sec, its.it_interval.tv_nsec);
    ret = timerfd_settime(
        fd_,
        0,
        &its,
        NULL
    );
    if (ret)
    {
        //todo: 错误处理
        return *this;
    }

    return *this;
}

int TimerFd::Create(int sec, int nsec, int intervalsec, int intervalnsec)
{
    fd_ = timerfd_create(
        CLOCK_REALTIME,
        TFD_NONBLOCK
    );
    if (fd_ == -1)
    {
        //todo: 错误处理
        printf("lxdebug1\n");
        return -1;
    }

    //itimerspec its;
    its.it_value.tv_sec = sec;
    its.it_value.tv_nsec = nsec;
    its.it_interval.tv_sec = intervalsec;
    its.it_interval.tv_nsec = intervalnsec;

    int ret = timerfd_settime(
        fd_,
        0,
        &its,
        NULL
    );
    if (ret)
    {
        //todo: 错误处理
        printf("lxdebug2\n");
        return -1;
    }
printf("fd:%d\n", fd_);
itimerspec its1;
    timerfd_gettime(fd_, &its1);
    printf("sec:%ld, nsec:%ld, intsec:%ld, intnsec:%ld, fd:%d\n", its1.it_value.tv_sec, its1.it_value.tv_nsec, its1.it_interval.tv_sec, its1.it_interval.tv_nsec, fd_);
    return fd_;
}

}}