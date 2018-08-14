#include <sys/time.h>
#include <iostream>
#include <cstdio>
#include <x/string/stringbuf.h>

const long long max_count = 100000000;
void test_stringbuf_newbuf();
void test_stringbuf_existbuf();
void test_stringbuf_newbuf_double();
void test_stringbuf_existbuf_double();
void test_snprintf();
void test_snprintf_double();
timeval timesub(const timeval& tv1, const timeval& tv2);

int main()
{
    test_stringbuf_newbuf();
    test_stringbuf_existbuf();
    test_stringbuf_newbuf_double();
    test_stringbuf_existbuf_double();
    test_snprintf();
    test_snprintf_double();
}

void test_stringbuf_newbuf()
{
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        x::stringbuf().init(7)
            .append("short:").append((short)12).append(". ")
            .append("unsigned short:").append((unsigned short)23).append(". ")
            .append("int:").append((int)34).append(". ")
            .append("unsigned int:").append((unsigned int)45).append(". ")
            .append("long:").append((long)56).append(". ")
            .append("unsigned long:").append((unsigned long)67).append(". ")
            .append("long long:").append((long long)78).append(". ")
            .append("unsigned long long:").append((unsigned long long)89).append(".")
            .buffer();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    std::cout<<"stringbuf newbuf:"<<tv.tv_sec<<"."<<tv.tv_usec<<std::endl;
}

void test_stringbuf_existbuf()
{
    char buf[1024];
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        x::stringbuf().init(buf, sizeof(buf))
            .append("short:").append((short)12).append(". ")
            .append("unsigned short:").append((unsigned short)23).append(". ")
            .append("int:").append((int)34).append(". ")
            .append("unsigned int:").append((unsigned int)45).append(". ")
            .append("long:").append((long)56).append(". ")
            .append("unsigned long:").append((unsigned long)67).append(". ")
            .append("long long:").append((long long)78).append(". ")
            .append("unsigned long long:").append((unsigned long long)89).append(".")
            .buffer();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    std::cout<<"stringbuf existbuf:"<<tv.tv_sec<<"."<<tv.tv_usec<<std::endl;
}

void test_stringbuf_newbuf_double()
{
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        x::stringbuf().init(7)
            .append("double1:").append(12.12).append(". ")
            .append("double2:").append(23.23).append(". ")
            .append("double3:").append(34.34).append(". ")
            .append("double4:").append(45.45).append(". ")
            .append("double5:").append(56.56).append(". ")
            .append("double6:").append(67.67).append(". ")
            .append("double7:").append(78.78).append(". ")
            .append("double8:").append(89.89).append(".")
            .buffer();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    std::cout<<"stringbuf newbuf double:"<<tv.tv_sec<<"."<<tv.tv_usec<<std::endl;
}

void test_stringbuf_existbuf_double()
{
    char buf[1024];
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        x::stringbuf().init(buf, sizeof(buf))
            .append("double1:").append(12.12).append(". ")
            .append("double2:").append(23.23).append(". ")
            .append("double3:").append(34.34).append(". ")
            .append("double4:").append(45.45).append(". ")
            .append("double5:").append(56.56).append(". ")
            .append("double6:").append(67.67).append(". ")
            .append("double7:").append(78.78).append(". ")
            .append("double8:").append(89.89).append(".")
            .buffer();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    std::cout<<"stringbuf existbuf double:"<<tv.tv_sec<<"."<<tv.tv_usec<<std::endl;
}

void test_snprintf()
{
    char buf[1024];
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        snprintf(buf, sizeof(buf), "short:%hd. unsigned short:%hu. int:%d. unsigned int:%u. long:%ld. unsigned long:%lu. long long:%lld. unsigned long long:%llu.",
                    (short)12, (unsigned short)23, (int)34, (unsigned int)45, (long)56, (unsigned long)67, (long long)78, (unsigned long long)89);
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    std::cout<<"snprintf:"<<tv.tv_sec<<"."<<tv.tv_usec<<std::endl;
}

void test_snprintf_double()
{
    char buf[1024];
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        snprintf(buf, sizeof(buf), "double1:%f. double2:%f. double3:%f. double4:%f. double5:%f. double6:%f. double7:%f. double8:%f.",
                    12.12, 23.23, 34.34, 45.45, 56.56, 67.67, 78.78, 89.89);
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    std::cout<<"snprintf double:"<<tv.tv_sec<<"."<<tv.tv_usec<<std::endl;
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

