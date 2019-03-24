#include "x/task/timer_task.h"
#include "timer_task_impl.h"


namespace x{namespace task {

TimerTask::~TimerTask()
{
}

x::task::TimerTask* TimerTask::Create()
{
    return new x::task::TimerTaskImpl;
}

void TimerTask::Destroy(x::task::TimerTask*& task)
{
    if (task)
    {
        delete task;
        task = nullptr;
    }
}

}}
