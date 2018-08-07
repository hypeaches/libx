#ifndef LIBX_STRING_IMPL_STRINGBUF_H
#define LIBX_STRING_IMPL_STRINGBUF_H

namespace x{namespace impl{

class stringbuf
{
public:
    stringbuf();
    ~stringbuf();

    void init(int len);

private:
    char* buf_;
    int buf_len_;
    char* tail_;
};

}}

#endif
