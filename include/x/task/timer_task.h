#ifndef LIBX_TASK_TIMER_TASK_H
#define LIBX_TASK_TIMER_TASK_H

#include "x/error/error_info.h"

namespace x{

namespace task{

class TimerTask {
public:
    virtual ~TimerTask();
    virtual void Destroy() = 0;
    virtual bool Init() = 0;
    virtual x::task::TimerTask* SetTaskFunc(bool(*func)(int, void*), void*) = 0;
    virtual x::task::TimerTask* At(int sec, int nsec) = 0;
    virtual x::task::TimerTask* After(int sec, int nsec) = 0;
    virtual x::task::TimerTask* Repeat(int sec, int nsec) = 0;
    virtual bool Run() = 0;
};

class Timer
{
public:
    virtual ~Timer();
    static x::task::Timer* Create();
    static void Destroy(x::task::Timer*& t);

    virtual x::task::TimerTask* CreateTask() = 0;
    virtual bool Init() = 0;
    virtual void CreateThreadPool(int thread_pool_size, int max_task_num) = 0;
};

}}

#endif