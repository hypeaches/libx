#ifndef LIBX_TASK_TIMER_TASK_H
#define LIBX_TASK_TIMER_TASK_H

namespace x{

struct ErrorInfo;

namespace task{

class TimerTask {
public:
    virtual ~TimerTask();
    virtual x::task::TimerTask* SetTaskFunc(void(*func)(void*), void*) = 0;
    virtual x::task::TimerTask* At(int sec, int nsec) = 0;
    virtual x::task::TimerTask* After(int sec, int nsec) = 0;
    virtual x::task::TimerTask* Repeat(int sec, int nsec) = 0;
    virtual x::task::TimerTask* Run() = 0;
};

class Timer
{
public:
    virtual ~Timer();
    static x::task::Timer* Create();
    static void Destroy(x::task::Timer*& t);
    static void DestroyTask(x::task::TimerTask*& task);

    virtual x::task::TimerTask* CreateTask() = 0;
    virtual int Init() = 0;
    virtual void CreateThreadPool(int thread_pool_size, int max_task_num) = 0;
};

}}

#endif