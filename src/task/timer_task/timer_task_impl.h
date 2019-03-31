#ifndef LIBX_TASK_TIMER_TASK_IMPL_H
#define LIBX_TASK_TIMER_TASK_IMPL_H

#include "x/task/timer_task.h"

namespace x{namespace task{

class TimerImpl;

class TimerTaskImpl : public x::task::TimerTask
{
public:
    TimerTaskImpl(x::task::TimerImpl* timer);
    virtual ~TimerTaskImpl();
    virtual void Destroy() override;
    virtual x::ErrorInfo Init() override;
    virtual x::task::TimerTask* SetTaskFunc(bool(*func)(int, void*), void*) override;
    virtual x::task::TimerTask* At(int sec, int nsec) override;
    virtual x::task::TimerTask* After(int sec, int nsec) override;
    virtual x::task::TimerTask* Repeat(int sec, int nsec) override;
    virtual x::ErrorInfo Run() override;

public:
    bool RunCallbackFunc();
    int Fd();
    void SetExpireCount(int expire_count);

private:
    int tfd_;
    int expire_count_;
    x::task::TimerImpl* timer_;
    bool(*func_)(int, void*);
    void* obj_;

    int sec_;
    int nsec_;
    int interval_sec_;
    int interval_nsec_;
    bool is_abs_time_;
};

}}

#endif