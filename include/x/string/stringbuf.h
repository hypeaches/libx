#ifndef LIBX_STRING_IMPL_STRINGBUF_H
#define LIBX_STRING_IMPL_STRINGBUF_H

#include <cstdint>

namespace x{

class stringbuf
{
public:
    stringbuf();
    stringbuf(int len);
    stringbuf(char* buf, int len);
    ~stringbuf();

    const char* buffer() const { return buf_; }
    char* moved_buffer();

    stringbuf& append(short int val);
    stringbuf& append(unsigned short int val);
    stringbuf& append(int val);
    stringbuf& append(unsigned int val);
    stringbuf& append(long int val);
    stringbuf& append(unsigned long int val);
    stringbuf& append(long long int val);
    stringbuf& append(unsigned long long int val);
    stringbuf& append(char val);
    stringbuf& append(const char* val);
    stringbuf& append(const char* val, int len);
    stringbuf& append(double val);

    stringbuf& pop_back();
    stringbuf& pop_back(char c);

    int size();

private:
    stringbuf& init(int len);
    stringbuf& init(char* buf, int len);
    bool increase();
    int new_buf_len();
    template <class T>
    friend int append_integer_to_buffer(char* buf, int buf_len, T val);
    template <class T>
    friend int append_to_buffer(const char* fmt, const T& val, stringbuf* strbuf);
    template <class T>
    friend int append_integer_to_buffer(const T& val, stringbuf* strbuf);

private:
    char* buf_;
    int len_;
    char* tail_;
    bool auto_managed_buf_;
};

}

#endif
