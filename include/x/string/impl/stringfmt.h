#ifndef LIBX_STRING_IMPL_STRINGFMT_H
#define LIBX_STRING_IMPL_STRINGFMT_H

namespace x {namespace impl{

class stringfmt
{
public:
    stringfmt();
    void set_fmt(const char* fmt);
    bool next(const char*& fmt, int& len);

private:
    const char* fmt_;
    int len_;
    const char* cur_;
};

}}

#endif // LIBX_STRING_IMPL_STRINGFMT_H
