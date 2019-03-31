#include "x/task/timer_task.h"
#include "timer_impl.h"
#include "timer_task_impl.h"


namespace x{namespace task {

TimerTask::~TimerTask()
{

}

Timer::~Timer()
{

}

x::task::Timer* Timer::Create()
{
    return new x::task::TimerImpl;
}

void Timer::Destroy(x::task::Timer*& t)
{
    delete t;
    t = nullptr;
}

}}
