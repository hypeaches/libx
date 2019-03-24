#ifndef LIBX_TASK_TIMER_IMPL_H
#define LIBX_TASK_TIMER_IMPL_H

#include <thread>
#include "x/task/thread_pool.h"
#include "x/task/timer_task.h"

namespace x{namespace task{

class TimerImpl : public x::task::Timer
{
public:
    TimerImpl();
    virtual ~TimerImpl();

    virtual x::task::TimerTask* CreateTask() override;
    virtual int Init() override;
    virtual void CreateThreadPool(int thread_pool_size, int max_task_num) override;

private:
    void epollThread();

private:
    int efd_;
    volatile bool running_;
    x::task::ThreadPool* tp_;
    std::thread epoll_thread_;
};

}}

#endif