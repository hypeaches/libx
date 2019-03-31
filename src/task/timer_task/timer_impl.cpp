#include "timer_impl.h"
#include "src/error/system_error_info.h"
#include <unistd.h>
#include <sys/epoll.h>
#include "x/task/thread_pool.h"
#include "timer_task_impl.h"

namespace x{namespace task{

TimerImpl::TimerImpl()
{
    efd_ = -1;
    running_ = false;
    tp_ = nullptr;
}

TimerImpl::~TimerImpl()
{
    if (tp_)
    {
        tp_->Stop();
        tp_->Wait();
        delete tp_;
    }
    for (auto& pair : tasks_)
    {
        delete pair.second;
    }
    tasks_.clear();
    if (efd_)
    {
        close(efd_);
    }
}

x::task::TimerTask* TimerImpl::CreateTask()
{
    return new x::task::TimerTaskImpl(this);
}

x::ErrorInfo TimerImpl::Init()
{
    efd_ = epoll_create1(0);
    if (efd_ == -1)
    {
        return ErrorInfo(new x::SystemErrorInfo(errno, "create epoll fd failed"));
    }
    running_ = true;
    epoll_thread_ = std::thread(&TimerImpl::epollThread, this);
    return x::ErrorInfo();
}

void TimerImpl::CreateThreadPool(int thread_pool_size, int max_task_num)
{
    if (!tp_)
    {
        tp_ = x::task::ThreadPool::Create();
        if (tp_)
        {
            tp_->SetPoolSize(thread_pool_size);
            tp_->SetMaxTaskNum(max_task_num);
            tp_->SetThreadFunc(TimerImpl::PoolThread);
            tp_->Start();
        }
    }
}

void TimerImpl::epollThread()
{
    int fdsz = 0;
    bool ret = false;
    uint64_t expire_count = 0;
    const int max_events_count = 8;
    epoll_event events[max_events_count];
    x::task::TimerTaskImpl* task = nullptr;
    while (running_)
    {
        fdsz = epoll_wait(efd_, events, max_events_count, 1000);
        for (int i = 0; running_ && i < fdsz; i++)
        {
            if (events[i].events && EPOLLIN)
            {
                task = static_cast<x::task::TimerTaskImpl*>(events[i].data.ptr);
                ssize_t sz = read(task->Fd(), &expire_count, sizeof(expire_count));
                if (sz != sizeof(expire_count))
                {
                    continue;
                }

                task->SetExpireCount(expire_count);
                if (tp_)
                {
                    tp_->Add(task);
                }
                else
                {
                    ret = task->RunCallbackFunc();
                    if (!ret)
                    {
                        task->Destroy();
                    }
                }
                
            }
        }
    }
}

void TimerImpl::DestroyTask(x::task::TimerTaskImpl* task)
{
    {
        std::lock_guard<std::mutex> lg(task_mutex_);
        tasks_.erase(task->Fd());
    }
    delete task;
}

void TimerImpl::PoolThread(void* param)
{
    x::task::TimerTaskImpl* task = static_cast<x::task::TimerTaskImpl*>(param);
    bool ret = task->RunCallbackFunc();
    if (!ret)
    {
        task->Destroy();
    }
}

}}