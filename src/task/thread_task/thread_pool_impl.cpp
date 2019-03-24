#include "thread_pool_impl.h"
#include <chrono>


namespace x {namespace task{

ThreadPoolImpl::ThreadPoolImpl()
{
    pool_size_ = static_cast<int>(std::thread::hardware_concurrency());
    func_ = nullptr;
    max_task_num_ = -1;
    running_ = false;
}

ThreadPoolImpl::~ThreadPoolImpl()
{
    this->Stop();
    this->Wait();
}

void ThreadPoolImpl::SetPoolSize(int pool_size)
{
    pool_size_ = (pool_size > 0) ? pool_size : static_cast<int>(std::thread::hardware_concurrency());
}

void ThreadPoolImpl::SetMaxTaskNum(int num)
{
    max_task_num_ = num;
}

void ThreadPoolImpl::SetThreadFunc(void(*func)(void*))
{
    func_ = func;
}

int  ThreadPoolImpl::GetPoolSize()
{
    return pool_size_;
}

int  ThreadPoolImpl::GetTaskMaxNum()
{
    return max_task_num_;
}

bool ThreadPoolImpl::Add(void* data)
{
    bool ret = false;
    {
        std::lock_guard<std::mutex> lk(data_pool_mutex_);
        if ((max_task_num_ < 0) || (data_pool_.size() < static_cast<std::size_t>(max_task_num_)))
        {
            ret = true;
            data_pool_.push(data);
        }
    }

    if (ret)
    {
        data_pool_cv_.notify_one();
    }

    return ret;
}

bool ThreadPoolImpl::Start()
{
    running_ = true;
    pool_.reserve(pool_size_);
    for (int i = 0; i < pool_size_; i++)
    {
        pool_.push_back(std::thread(&ThreadPoolImpl::ThreadWork, this));
    }

    return true;
}

bool ThreadPoolImpl::Stop()
{
    running_ = false;
    return true;
}

bool ThreadPoolImpl::Wait()
{
    for (auto& thrd : pool_)
    {
        if (thrd.joinable())
        {
            thrd.join();
        }
    }
    return true;
}

void ThreadPoolImpl::ThreadWork()
{
    bool next = false;
    void* data = nullptr;
    while (running_)
    {
        next = false;
        data = nullptr;
        {
            std::unique_lock<std::mutex> lk(data_pool_mutex_);
            while(running_ && data_pool_.empty()){
                data_pool_cv_.wait_for(lk, std::chrono::seconds(1));
            }
            if (!data_pool_.empty())
            {
                data = data_pool_.front();
                data_pool_.pop();
                next = true;
            }
        }

        while (next)
        {
            (*func_)(data);
            std::lock_guard<std::mutex> lk(data_pool_mutex_);
            if (data_pool_.empty())
            {
                break;
            }
            else
            {
                data = data_pool_.front();
                data_pool_.pop();
            }
        }
    }
}

}}