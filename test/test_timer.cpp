#include <unistd.h>
#include <ctime>
#include <iostream>
#include <x/error/error_info.h>
#include <x/task/timer_task.h>

bool func(int count, void*)
{
    static time_t last_time = 0;
    time_t current_time = time(NULL);
    std::cout<<count<<". current time:"<<current_time<<". diff:"<<(current_time - last_time)<<std::endl;
    last_time = current_time;
    return true;
}

int main()
{
    x::task::Timer* tm = x::task::Timer::Create();
    if (!tm->Init())
    {
        std::cout<<x::ErrorInfo::GetErrorInfo()->Message()<<std::endl;
        return 1;
    }
    x::task::TimerTask* tt = tm->CreateTask();
    if (!tt->Init())
    {
        std::cout<<x::ErrorInfo::GetErrorInfo()->Message()<<std::endl;
        return 2;
    }
    tt->SetTaskFunc(&func, NULL)
        ->After(1, 0)
        ->Repeat(3, 0)
        ->Run();
    sleep(100);

    tt->Destroy();
    x::task::Timer::Destroy(tm);
    return 0;
}