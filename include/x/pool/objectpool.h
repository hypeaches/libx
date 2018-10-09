#ifndef LIBX_POOL_OBJECTPOOL_H
#define LIBX_POOL_OBJECTPOOL_H

#include <vector>
#include "x/pool/globalpool.h"

namespace x{

template <class T, class AllocatorType = x::globalpool<T>>
class objectpool
{
public:
    static int init(int count);
    static T* create();
    static void release(T* obj);

private:
    static AllocatorType allocator_;
    static thread_local std::vector<T*> pool_;
};

template <class T, class AllocatorType>
AllocatorType objectpool<T, AllocatorType>::allocator_;

template <class T, class AllocatorType>
thread_local std::vector<T*> objectpool<T, AllocatorType>::pool_;

template <class T, class AllocatorType>
int objectpool<T, AllocatorType>::init(int count)
{
    return allocator_.init(count);
}

template <class T, class AllocatorType>
T* objectpool<T, AllocatorType>::create()
{
    T* obj = nullptr;
    if (pool_.empty())
    {
        obj = allocator_.create();
    }
    else
    {
        obj = pool_.back();
        pool_.pop_back();
    }
    return obj;
}

template <class T, class AllocatorType>
void objectpool<T, AllocatorType>::release(T* obj)
{
    pool_.push_back(obj);
}

}

#endif
