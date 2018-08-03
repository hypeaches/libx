#include "x/string/stringbuilder.h"
#include <cstring>

namespace x {

namespace {
const int default_buffer_size = 4096;
}

stringbuilder::stringbuilder()
{
    buf_max_size_ = default_buffer_size;
    buf_ = new char[buf_max_size_];
}

stringbuilder::stringbuilder(int buflen)
{
    buf_max_size_ = buflen;
    buf_ = new char[buf_max_size_];
}

stringbuilder::~stringbuilder()
{
    if (buf_)
    {
        delete buf_;
    }
}

stringbuilder::stringbuilder(stringbuilder&&)
{}
stringbuilder::stringbuilder(const stringbuilder&)
{}
stringbuilder& stringbuilder::operator=(const stringbuilder&)
{
    return *this;
}

void stringbuilder::test()
{
}

}
