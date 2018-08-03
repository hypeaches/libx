#include "x/string/impl/stringfmt.h"
#include <cstring>

namespace x {namespace impl{

stringfmt::stringfmt()
{
    fmt_ = nullptr;
    len_ = 0;
    cur_ = nullptr;
}

void stringfmt::set_fmt(const char* fmt)
{
    if (!fmt) return;
    fmt_ = fmt;
    len_ = strlen(fmt);
    cur_ = fmt;
}

bool stringfmt::next(const char*& fmt, int& len)
{
    if (!cur_)
    {
        fmt = nullptr;
        len = 0;
        return false;
    }

    if (cur_ - fmt_ == len_)
    {
        fmt = nullptr;
        len = 0;
        return false;
    }

    fmt = cur_;
    while ((*cur_ != '%') && (cur_ - fmt_ < len_))
    {
        ++cur_;
    }
    if (cur_ - fmt_ == len_)
    {
        len = len_;
        return false;
    }
    if (cur_ - fmt_ + 1 == len_)
    {
        len = cur_ - fmt;
        ++cur_;
        return false;
    }

    bool ret = false;
    if (cur_[1] == '%')
    {
        ++cur_;
        ret = true;
    }
    len = cur_ - fmt;
    ++cur_;
    return ret;
}

}}
