#include "x/task/thread_pool.h"
#include "thread_pool_impl.h"

namespace x{namespace task{

ThreadPool::~ThreadPool()
{

}

x::task::ThreadPool* ThreadPool::Create()
{
    return new ThreadPoolImpl;
}

void ThreadPool::Destroy(ThreadPool*& pool)
{
    if (pool)
    {
        delete pool;
        pool = nullptr;
    }
}

}}
