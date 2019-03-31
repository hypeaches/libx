#ifndef LIBX_TASK_THREAD_POOL_IMPL_H
#define LIBX_TASK_THREAD_POOL_IMPL_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include "x/task/thread_pool.h"

namespace x {namespace task {

class ThreadPoolImpl : public x::task::ThreadPool
{
public:
    ThreadPoolImpl();
    virtual ~ThreadPoolImpl();
    virtual void SetPoolSize(int pool_size) override;
    virtual void SetMaxTaskNum(int num) override;
    virtual void SetThreadFunc(void(*func)(void*)) override;

    virtual int GetPoolSize() override;
    virtual int GetTaskMaxNum() override;

    virtual bool Add(void*) override;
    virtual bool Start() override;
    virtual bool Stop() override;
    virtual bool Wait() override;
    void ThreadWork();

private:
    int pool_size_;
    void(*func_)(void*);
    volatile int max_task_num_;
    volatile bool running_;
    std::vector<std::thread> pool_;
    std::queue<void*> data_pool_;
    std::mutex data_pool_mutex_;
    std::condition_variable data_pool_cv_;
};

}}

#endif