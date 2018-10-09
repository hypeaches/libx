#ifndef LIBX_POOL_GLOBALPOOL_H
#define LIBX_POOL_GLOBALPOOL_H

#include <mutex>
#include <vector>

namespace x{

template <class T>
class globalpool
{
public:
    ~globalpool();
    int init(int count);
    T* create();
    void release(T* obj);

    int expand_size() const { return expand_size_; }
    int expand_size(int count) { expand_size_ = count; }

private:
    void expand();

private:
    int expand_size_;
    std::mutex mtx_;
    std::vector<T*> head_;
    std::vector<T*> pool_;
};

template <class T>
globalpool<T>::~globalpool()
{
    std::lock_guard<std::mutex> lock(mtx_);
    for (T*& obj : head_)
    {
        delete[] obj;
        obj = nullptr;
    }
    head_.clear();
    pool_.clear();
}

template <class T>
int globalpool<T>::init(int count)
{
    expand_size_ = count;
    expand();
    return 0;
}

template <class T>
T* globalpool<T>::create()
{
    T* obj = nullptr;
    std::lock_guard<std::mutex> lock(mtx_);
    if (pool_.empty())
    {
        expand();
    }
    if (!pool_.empty())
    {
        obj = pool_.back();
        pool_.pop_back();
    }
    return obj;
}

template <class T>
void globalpool<T>::release(T* obj)
{
    std::lock_guard<std::mutex> lock(mtx_);
    pool_.push_back(obj);
}

template <class T>
void globalpool<T>::expand()
{
    T* objs = new T[expand_size_];
    head_.push_back(objs);
    for (int i = 0; i < expand_size_; i++)
    {
        pool_.push_back(&objs[i]);
    }
}

}

#endif
