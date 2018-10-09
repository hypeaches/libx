#include <sys/time.h>
#include <cstdint>
#include <vector>
#include <thread>
#include <iostream>
#include <iomanip>
#include <x/pool/objectpool.h>

uint64_t max_count = 100000000;
uint64_t thrds_count = 4;

struct MyStruct
{
    char buf[1024];
    double d1;

    MyStruct()
    {
        for (int i = 0; i < sizeof(buf); i++)
        {
            buf[i] = 0;
        }
        d1 = 0.0;
    }
};

timeval timesub(const timeval& tv1, const timeval& tv2);
void print(const char* str, const timeval& tv);

void test_object_pool();
void test_new();

int main()
{
    x::objectpool<MyStruct>::init(32);
    test_object_pool();
    test_new();
}

void test_object_pool_thread()
{
    MyStruct* ms = nullptr;
    uint64_t count = max_count / thrds_count;
    for (uint64_t i = 0; i < count; i++)
    {
        ms = x::objectpool<MyStruct>::create();
        if (ms)
        {
            x::objectpool<MyStruct>::release(ms);
        }
        else
        {
            printf("pool null\n");
        }
    }
}

void test_object_pool()
{
    std::vector<std::thread> thrds;
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (int i = 0; i < thrds_count; i++)
    {
        thrds.push_back(std::thread(&test_object_pool_thread));
    }
    for (auto& thrd : thrds)
    {
        thrd.join();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("threads of object pool:", tv);
}

void test_new_thread()
{
    MyStruct* ms = nullptr;
    uint64_t count = max_count / thrds_count;
    for (uint64_t i = 0; i < count; i++)
    {
        ms = new MyStruct;
        if (ms)
        {
            delete ms;
        }
        else
        {
            printf("new null\n");
        }
    }
}

void test_new()
{
    std::vector<std::thread> thrds;
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (int i = 0; i < thrds_count; i++)
    {
        thrds.push_back(std::thread(&test_new_thread));
    }
    for (auto& thrd : thrds)
    {
        thrd.join();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("threads of new:", tv);
}

timeval timesub(const timeval& tv1, const timeval& tv2)
{
    timeval tv;
    tv.tv_sec = tv2.tv_sec - tv1.tv_sec;
    tv.tv_usec = tv2.tv_usec - tv1.tv_usec;
    if (tv.tv_sec > 0 && tv.tv_usec < 0)
    {
        tv.tv_sec -= 1;
        tv.tv_usec += 1000000;
    }
    return tv;
}

void print(const char* str, const timeval& tv)
{
    std::cout<<std::setw(27)<<str<<":"<<tv.tv_sec<<"."<<tv.tv_usec<<std::endl;
}
