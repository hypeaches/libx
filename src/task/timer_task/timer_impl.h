#ifndef LIBX_TASK_TIMER_IMPL_H
#define LIBX_TASK_TIMER_IMPL_H

#include <map>
#include <mutex>
#include <thread>
#include "x/task/thread_pool.h"
#include "x/task/timer_task.h"

namespace x{namespace task{

class TimerTaskImpl;

class TimerImpl : public x::task::Timer
{
public:
    TimerImpl();
    virtual ~TimerImpl();

    virtual x::task::TimerTask* CreateTask() override;
    virtual x::ErrorInfo Init() override;
    virtual void CreateThreadPool(int thread_pool_size, int max_task_num) override;

public:
    int Fd() { return efd_; }
    static void PoolThread(void* param);
    void DestroyTask(x::task::TimerTaskImpl* task);

private:
    void epollThread();

private:
    int efd_;
    volatile bool running_;
    x::task::ThreadPool* tp_;
    std::thread epoll_thread_;
    std::mutex task_mutex_;
    std::map<int, x::task::TimerTask*> tasks_;
};

}}

#endif