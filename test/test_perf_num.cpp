#include <sys/time.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <x/string/stringbuf.h>

//const long long max_count = 100000000;
const long long max_count = 100000000;
void test_stringbuf_newbuf();
void test_stringbuf_existbuf();
void test_stringbuf_existbuf_string();
void test_stringbuf_newbuf_integer();
void test_stringbuf_existbuf_integer();
void test_stringbuf_newbuf_double();
void test_stringbuf_existbuf_double();

void test_stringstream_newbuf();
void test_stringstream_newbuf_string();
void test_stringstream_newbuf_integer();
void test_stringstream_newbuf_double();

void test_snprintf();
void test_snprintf_string();
void test_snprintf_integer();
void test_snprintf_double();

timeval timesub(const timeval& tv1, const timeval& tv2);
void print(const char* str, const timeval& tv);

int main()
{
    test_stringbuf_newbuf();
    test_stringbuf_existbuf();
    test_stringbuf_existbuf_string();
    test_stringbuf_newbuf_integer();
    test_stringbuf_existbuf_integer();
    test_stringbuf_newbuf_double();
    test_stringbuf_existbuf_double();

    test_stringstream_newbuf();
    test_stringstream_newbuf_string();
    test_stringstream_newbuf_integer();
    test_stringstream_newbuf_double();

    test_snprintf();
    test_snprintf_string();
    test_snprintf_integer();
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
    print("stringbuf newbuf", tv);
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
    print("stringbuf existbuf", tv);
}

void test_stringbuf_existbuf_string()
{
    char buf[1024];
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        x::stringbuf().init(buf, sizeof(buf))
            .append("abc")
            .append("aaaaaaaaaaaaaaaaaaaaaaaaaa")
            .append("aabbccddeeff")
            .append("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")
            .append("ccccc")
            .append("dd")
            .append("e")
            .append("hgiuleif")
            .buffer();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("stringbuf existbuf string", tv);
}

void test_stringbuf_newbuf_integer()
{
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        x::stringbuf().init(7)
            .append((short)12)
            .append((unsigned short)23)
            .append((int)34)
            .append((unsigned int)45)
            .append((long)56)
            .append((unsigned long)67)
            .append((long long)78)
            .append((unsigned long long)89)
            .buffer();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("stringbuf newbuf integer", tv);
}

void test_stringbuf_existbuf_integer()
{
    char buf[1024];
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        x::stringbuf().init(buf, sizeof(buf))
            .append((short)12)
            .append((unsigned short)23)
            .append((int)34)
            .append((unsigned int)45)
            .append((long)56)
            .append((unsigned long)67)
            .append((long long)78)
            .append((unsigned long long)89)
            .buffer();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("stringbuf existbuf integer", tv);
}

void test_stringbuf_newbuf_double()
{
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        x::stringbuf().init(7)
            .append(12.12)
            .append(23.23)
            .append(34.34)
            .append(45.45)
            .append(56.56)
            .append(67.67)
            .append(78.78)
            .append(89.89)
            .buffer();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("stringbuf newbuf double", tv);
}

void test_stringbuf_existbuf_double()
{
    char buf[1024];
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        x::stringbuf().init(buf, sizeof(buf))
            .append(12.12)
            .append(23.23)
            .append(34.34)
            .append(45.45)
            .append(56.56)
            .append(67.67)
            .append(78.78)
            .append(89.89)
            .buffer();
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("stringbuf existbuf double", tv);
}

void test_stringstream_newbuf()
{
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        std::ostringstream oss;
        oss
            <<("short:")<<((short)12)<<(". ")
            <<("unsigned short:")<<((unsigned short)23)<<(". ")
            <<("int:")<<((int)34)<<(". ")
            <<("unsigned int:")<<((unsigned int)45)<<(". ")
            <<("long:")<<((long)56)<<(". ")
            <<("unsigned long:")<<((unsigned long)67)<<(". ")
            <<("long long:")<<((long long)78)<<(". ")
            <<("unsigned long long:")<<((unsigned long long)89)<<(".");
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("stringstream", tv);
}

void test_stringstream_newbuf_string()
{
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        std::ostringstream oss;
        oss
            <<("abc")
            <<("aaaaaaaaaaaaaaaaaaaaaaaaaa")
            <<("aabbccddeeff")
            <<("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")
            <<("ccccc")
            <<("dd")
            <<("e")
            <<("hgiuleif");
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("stringstream string", tv);
}

void test_stringstream_newbuf_integer()
{
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        std::ostringstream oss;
        oss
            <<((short)12)
            <<((unsigned short)23)
            <<((int)34)
            <<((unsigned int)45)
            <<((long)56)
            <<((unsigned long)67)
            <<((long long)78)
            <<((unsigned long long)89);
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("stringstream integer", tv);
}

void test_stringstream_newbuf_double()
{
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        std::ostringstream oss;
        oss
            <<(12.12)
            <<(23.23)
            <<(34.34)
            <<(45.45)
            <<(56.56)
            <<(67.67)
            <<(78.78)
            <<(89.89);
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("stringstream double", tv);
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
    print("snprintf", tv);
}

void test_snprintf_string()
{
    char buf[1024];
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        snprintf(buf, sizeof(buf), "%s%s%s%s%s%s%s%s",
            ("abc"),
            ("aaaaaaaaaaaaaaaaaaaaaaaaaa"),
            ("aabbccddeeff"),
            ("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"),
            ("ccccc"),
            ("dd"),
            ("e"),
            ("hgiuleif"));
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("snprintf string", tv);
}

void test_snprintf_integer()
{
    char buf[1024];
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        snprintf(buf, sizeof(buf), "%hd%hu%d%u%ld%lu%lld%llu.",
                    (short)12, (unsigned short)23, (int)34, (unsigned int)45, (long)56, (unsigned long)67, (long long)78, (unsigned long long)89);
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("snprintf integer", tv);
}

void test_snprintf_double()
{
    char buf[1024];
    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (long long i = 0; i < max_count; ++i)
    {
        snprintf(buf, sizeof(buf), "%f%f%f%f%f%f%f%f",
                    12.12, 23.23, 34.34, 45.45, 56.56, 67.67, 78.78, 89.89);
    }
    gettimeofday(&tv2, NULL);
    timeval tv = timesub(tv1, tv2);
    print("snprintf double", tv);
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

