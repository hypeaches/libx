#ifndef LIBX_REFERENCECOUNT_H
#define LIBX_REFERENCECOUNT_H

#include <atomic>

namespace x{

template <class T>
struct reference_count_mem
{
    reference_count_mem()
        : ref_count_(1)
        , obj(T())
    {}
    std::atomic<int> ref_count_;
    T obj;
};

template <class T>
class reference_count
{
public:
    reference_count();
    reference_count(reference_count&& other);
    reference_count(const reference_count& other);
    ~reference_count();

    reference_count& operator=(reference_count&& other);
    reference_count& operator=(const reference_count& other);

private:
    void destroy();

private:
    reference_count_mem<T>* mem_;
};

template <class T>
reference_count::reference_count()
{
    mem_ = new reference_count_mem<T>;
}

template <class T>
reference_count::reference_count(reference_count&& other)
{
    mem_ = other.mem_;
    other.mem_ = nullptr;
}

template <class T>
reference_count::reference_count(const reference_count& other)
{
    other.mem_->ref_count_.fetch_add(1);
    mem_ = other.mem_;
}

template <class T>
reference_count& reference_count::operator=(reference_count&& other)
{
    if (this == &other)
    {
        return *this;
    }
    destroy();
    mem_ = other.mem_;
    other.mem_ = nullptr;
    return *this;
}

template <class T>
reference_count& reference_count::operator=(const reference_count& other)
{
    if (this == &other)
    {
        return *this;
    }
    destroy();
    other.mem_->ref_count_.fetch_add(1);
    mem_ = other.mem_;
    return *this;
}

template <class T>
reference_count::~reference_count()
{
    destroy();
}

template <class T>
void reference_count::destroy()
{
    if (!mem_)
    {
        return;
    }

    int ref = mem_->ref_count_.fetch_sub(1);
    if (ref == 1)
    {
        delete mem_;
        mem_ = nullptr;
    }
}

}

#endif
