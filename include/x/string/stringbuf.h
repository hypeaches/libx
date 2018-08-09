#ifndef LIBX_STRING_IMPL_STRINGBUF_H
#define LIBX_STRING_IMPL_STRINGBUF_H

namespace x{

class stringbuf
{
public:
    stringbuf();
    ~stringbuf();

    stringbuf& init(int len);

private:
    void increase();
    int new_buf_len();

private:
    char* buf_;
    int len_;
    char* tail_;
};

}

#endif
