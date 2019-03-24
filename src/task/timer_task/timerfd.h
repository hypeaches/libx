#ifndef LIBX_TASK_TIMERFD_H
#define LIBX_TASK_TIMERFD_H

#include <sys/timerfd.h>

namespace x{namespace task{

class TimerFd
{
public:
    TimerFd();
    ~TimerFd();
    int Fd();// { return fd_; }
    int Move();
    TimerFd& Create();
    TimerFd& SetTime(int sec, int nsec);
    TimerFd& SetRepeat(int sec, int nsec);
    int Create(int sec, int nsec, int intervalsec, int intervalnsec);

private:
    int fd_;
    itimerspec its;
};

}}

#endif