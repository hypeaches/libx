#include <iostream>
#include <cstdio>
#include <x/string/stringbuf.h>

int main()
{
    std::cout<<x::stringbuf().init(2)
        .append("short:").append((short)12).append(". ")
        .append("unsigned short:").append((unsigned short)23).append(". ")
        .append("int:").append((int)34).append(". ")
        .append("unsigned int:").append((unsigned int)45).append(". ")
        .append("long:").append((long)56).append(". ")
        .append("unsigned long:").append((unsigned long)67).append(". ")
        .append("long long:").append((long long)78).append(". ")
        .append("unsigned long long:").append((unsigned long long)89).append(".")
        .buffer()
        <<std::endl;
    printf("%s\n", x::stringbuf().init(2)
        .append("short:").append((short)12).append(". ")
        .append("unsigned short:").append((unsigned short)23).append(". ")
        .append("int:").append((int)34).append(". ")
        .append("unsigned int:").append((unsigned int)45).append(". ")
        .append("long:").append((long)56).append(". ")
        .append("unsigned long:").append((unsigned long)67).append(". ")
        .append("long long:").append((long long)78).append(". ")
        .append("unsigned long long:").append((unsigned long long)89).append(".")
        .buffer());
    return 0;
}
