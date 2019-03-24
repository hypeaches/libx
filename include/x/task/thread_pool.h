#ifndef LIBX_TASK_THREAD_POOL_H
#define LIBX_TASK_THREAD_POOL_H

namespace x{namespace task{

class ThreadPool
{
public:
    static x::task::ThreadPool* Create();
    static void Destroy(ThreadPool*& pool);

    virtual ~ThreadPool();
    virtual void SetPoolSize(int pool_size) = 0;
    virtual void SetMaxTaskNum(int num) = 0;
    virtual void SetThreadFunc(void(*func)(void*)) = 0;

    virtual int GetPoolSize() = 0;
    virtual int GetTaskMaxNum() = 0;

    virtual bool Add(void*) = 0;
    virtual bool Start() = 0;
    virtual bool Stop() = 0;
    virtual bool Wait() = 0;
};

}}

#endif