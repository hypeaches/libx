#include "x/string/stringbuilder.h"
#include <cstring>

namespace x {

namespace {
const int default_buffer_size = 4096;
}

template <class T>
int append_to_buffer(T val, stringbuilder* sb)
{
    int len = 0;
    const char* fmt = nullptr;
    bool next = sb->fmt_.next(fmt, len);
    if (fmt)
    {
        sb->buf_.append(fmt, len);
        while (next)
        {
            next = sb->fmt_.next(fmt, len);
            sb->buf_.append(fmt, len);
        }
    }
    sb->buf_.append(val);
    return 1;
}

stringbuilder::stringbuilder()
        : buf_(default_buffer_size)
{
}

stringbuilder::stringbuilder(int len)
        : buf_(len)
{
}

stringbuilder::stringbuilder(char* buf, int len)
        : buf_(buf, len)
{
}

stringbuilder::~stringbuilder()
{
}

stringbuilder::stringbuilder(stringbuilder&&)
{}
stringbuilder::stringbuilder(const stringbuilder&)
{}
stringbuilder& stringbuilder::operator=(const stringbuilder&)
{
    return *this;
}

stringbuilder& stringbuilder::format(const char* fmt)
{
    fmt_.set_fmt(fmt);
    return *this;
}

stringbuilder& stringbuilder::arg(short int val)
{
    append_to_buffer(val, this);
    return *this;
}

stringbuilder& stringbuilder::arg(unsigned short int val)
{
    append_to_buffer(val, this);
    return *this;
}

stringbuilder& stringbuilder::arg(int val)
{
    append_to_buffer(val, this);
    return *this;
}

stringbuilder& stringbuilder::arg(unsigned int val)
{
    append_to_buffer(val, this);
    return *this;
}

stringbuilder& stringbuilder::arg(long int val)
{
    append_to_buffer(val, this);
    return *this;
}

stringbuilder& stringbuilder::arg(unsigned long int val)
{
    append_to_buffer(val, this);
    return *this;
}

stringbuilder& stringbuilder::arg(long long int val)
{
    append_to_buffer(val, this);
    return *this;
}

stringbuilder& stringbuilder::arg(unsigned long long int val)
{
    append_to_buffer(val, this);
    return *this;
}

stringbuilder& stringbuilder::arg(char val)
{
    append_to_buffer(val, this);
    return *this;
}

stringbuilder& stringbuilder::arg(const char* val)
{
    append_to_buffer(val, this);
    return *this;
}

stringbuilder& stringbuilder::arg(double val)
{
    append_to_buffer(val, this);
    return *this;
}

const char* stringbuilder::buffer()
{
    return buf_.buffer();
}

char* stringbuilder::moved_buffer()
{
    return buf_.moved_buffer();
}

}
