#include "x/string/stringbuilder.h"
#include <cstring>

namespace x {

namespace {
const int default_buffer_size = 4096;
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

}
