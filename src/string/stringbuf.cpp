#include "x/string/stringbuf.h"
#include <cstring>
#include <cstdio>

namespace x {

namespace {
const int default_buf_len = 4 * 1024;
const int expand_len_pos1 = 1 * 1024 * 1024;
const int expand2 = 64 * 1024;
const int expand_len_pos2 = 10 * 1024 * 1024;
const int expand3 = 1 * 1024 * 1024;
}

template <class T>
int append_integer_to_buffer(char* buf, int buf_len, T val)
{
    if (!buf || buf_len <= 0)
    {
        return -1;
    }

    int count = 0;
    if (val < 0)
    {
        *buf = '-';
        --buf_len;
        val = -val;
        ++count;
    }

    char* tail = buf;
    T num = 0;
    while (buf_len > 0 && val)
    {
        num = val % 10;
        val /= 10;
        *tail = num + '0';
        ++tail;
        --buf_len;
        ++count;
    }
    if (buf_len > 0)
    {
        *tail = 0;
    }
    return count;
}

template <class T>
int append_to_buffer(const char* fmt, const T& val, stringbuf* strbuf)
{
    int buf_len = strbuf->len_ - (strbuf->tail_ - strbuf->buf_);
    int len = snprintf(strbuf->tail_, buf_len, fmt, val);
    if (len < 0)
    {
        //todo: encoding error
    }
    else if (len == 0)
    {
        //todo: error
    }
    else if (len < buf_len)
    {
        //todo: ok
    }
    else
    {
        if (strbuf->increase())
        {
            buf_len = strbuf->len_ - (strbuf->tail_ - strbuf->buf_);
            len = snprintf(strbuf->tail_, buf_len, fmt, val);
        }
    }
    if (len > 0 && len < buf_len)
    {
        strbuf->tail_ += len;
    }
    else
    {
        *(strbuf->tail_) = 0;
    }
    return len;
}

template <class T>
int append_integer_to_buffer(const T& val, stringbuf* strbuf)
{
    int buf_len = strbuf->len_ - (strbuf->tail_ - strbuf->buf_);
    int len = append_integer_to_buffer(strbuf->tail_, buf_len, val);
    if (len < 0)
    {
        //todo: encoding error
    }
    else if (len == 0)
    {
        //todo: error
    }
    else if (len < buf_len)
    {
        //todo: ok
    }
    else
    {
        if (strbuf->increase())
        {
            buf_len = strbuf->len_ - (strbuf->tail_ - strbuf->buf_);
            len = append_integer_to_buffer(strbuf->tail_, buf_len, val);
        }
    }
    if (len > 0 && len < buf_len)
    {
        strbuf->tail_ += len;
    }
    else
    {
        *(strbuf->tail_) = 0;
    }
    return len;
}

stringbuf::stringbuf()
{
    buf_ = nullptr;
    len_ = 0;
    tail_ = nullptr;
    auto_managed_buf_ = false;
}

stringbuf::~stringbuf()
{
    if (auto_managed_buf_ && buf_)
    {
        delete buf_;
        buf_ = nullptr;
        len_ = 0;
        tail_ = nullptr;
        auto_managed_buf_ = false;
    }
}

stringbuf& stringbuf::init(char* buf, int len)
{
    buf_ = buf;
    len_ = len;
    tail_ = buf;
    auto_managed_buf_ = false;
    return *this;
}

stringbuf& stringbuf::init(int len)
{
    len_ = (len > 0) ? len : default_buf_len;
    buf_ = new char[len_];
    tail_ = buf_;
    auto_managed_buf_ = true;
    return *this;
}

bool stringbuf::increase()
{
    if (auto_managed_buf_)
    {
        int curlen = tail_ - buf_;
        int newlen = new_buf_len();
        char* oldbuf = buf_;
        char* newbuf = new char[newlen];

        memcpy(newbuf, buf_, curlen);
        newbuf[curlen] = 0;
        len_ = newlen;
        buf_ = newbuf;
        tail_ = buf_ + curlen;
        delete oldbuf;
    }
    return auto_managed_buf_;
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

stringbuf& stringbuf::append(short int val)
{
    //append_to_buffer("%hd", val, this);
    append_integer_to_buffer(val, this);
    return *this;
}

stringbuf& stringbuf::append(unsigned short int val)
{
    //append_to_buffer("%hu", val, this);
    append_integer_to_buffer(val, this);
    return *this;
}

stringbuf& stringbuf::append(int val)
{
    //append_to_buffer("%d", val, this);
    append_integer_to_buffer(val, this);
    return *this;
}

stringbuf& stringbuf::append(unsigned int val)
{
    //append_to_buffer("%u", val, this);
    append_integer_to_buffer(val, this);
    return *this;
}

stringbuf& stringbuf::append(long int val)
{
    //append_to_buffer("%ld", val, this);
    append_integer_to_buffer(val, this);
    return *this;
}

stringbuf& stringbuf::append(unsigned long int val)
{
    //append_to_buffer("%lu", val, this);
    append_integer_to_buffer(val, this);
    return *this;
}

stringbuf& stringbuf::append(long long int val)
{
    //append_to_buffer("%lld", val, this);
    append_integer_to_buffer(val, this);
    return *this;
}

stringbuf& stringbuf::append(unsigned long long int val)
{
    //append_to_buffer("%llu", val, this);
    append_integer_to_buffer(val, this);
    return *this;
}

stringbuf& stringbuf::append(char val)
{
    append_to_buffer("%d", (int)val, this);
    return *this;
}

stringbuf& stringbuf::append(const char* val)
{
    if (!val)
    {
        return *this;
    }

    int len = strlen(val);
    int curlen = len_ - (tail_ - buf_);
    bool ok = true;
    if (curlen <= len)
    {
        ok = increase();
    }
    if (ok)
    {
        memcpy(tail_, val, len);
        tail_ += len;
        *tail_ = 0;
    }
    return *this;
}

stringbuf& stringbuf::append(double val)
{
    append_to_buffer("%f", val, this);
    return *this;
}

}
