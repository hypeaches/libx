#include "x/string/stringbuf.h"

namespace x {

namespace {
const int default_buf_len = 4 * 1024;
const int expand_len_pos1 = 1 * 1024 * 1024;
const int expand2 = 64 * 1024;
const int expand_len_pos2 = 10 * 1024 * 1024;
const int expand3 = 1 * 1024 * 1024;
}

stringbuf::stringbuf()
{
    buf_ = nullptr;
    len_ = 0;
    tail_ = nullptr;
}

stringbuf::~stringbuf()
{
    if (buf_)
    {
        delete buf_;
        buf_ = nullptr;
        len_ = 0;
        tail_ = nullptr;
    }
}

stringbuf& stringbuf::init(int len)
{
    len_ = (len > 0) ? len : default_buf_len;
    buf_ = new char[len_];
    tail_ = buf_;
    return *this;
}

void stringbuf::increase()
{
    int curlen = tail_ - buf_;
    char* newbuf = nullptr;
    int newlen = new_buf_len();
}

int stringbuf::new_buf_len()
{
    int newlen = 0;
    if (len_ < expand_len_pos1)
    {
        newlen = len_ + len_;
    }
    else if (len_ < expand_len_pos2)
    {
        newlen = len_ + expand2;
    }
    else
    {
        newlen = len_ + expand3;
    }
    return newlen;
}

}
