#ifndef LIBX_TASK_TIMER_TASK_IMPL_H
#define LIBX_TASK_TIMER_TASK_IMPL_H

#include <thread>
#include <unordered_set>
#include "x/task/timer_task.h"

namespace x{namespace task{

class ThreadPool;

class TimerTaskImpl : public x::task::TimerTask
{
public:
    TimerTaskImpl();
    virtual ~TimerTaskImpl();
    virtual bool Init() override;
    virtual void SetTask(void(*func)(void*), void*) override;
    virtual void SetBackgroundTask(int thread_pool_size, int max_task_num) override;
    virtual int RunAt(int sec, int nsec) override;
    virtual int RunAfter(int sec, int nsec) override;
    virtual int RepeatAt(int sec, int nsec, int intval_sec, int interval_nsec) override;
    virtual int RepeatAfter(int sec, int nsec, int intval_sec, int interval_nsec) override;

private:
    void epollThread();

private:
    int efd_;
    volatile bool running_;
    void* callback_param_;
    void(*callback_)(void*);
    x::task::ThreadPool* tp_;
    std::thread epoll_thread_;
    std::unordered_set<int> tfds_;
};

}}

#endif