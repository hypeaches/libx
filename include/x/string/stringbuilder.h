#ifndef LIBX_STRING_STRINGBUILDER_H
#define LIBX_STRING_STRINGBUILDER_H

#include "x/string/stringbuf.h"
#include "x/string/impl/stringfmt.h"

namespace x {

class stringbuilder {
public:
    stringbuilder();
    stringbuilder(int len);
    stringbuilder(char* buf, int len);
    ~stringbuilder();

    stringbuilder& format(const char* fmt);

    stringbuilder& arg(short int val);
    stringbuilder& arg(unsigned short int val);
    stringbuilder& arg(int val);
    stringbuilder& arg(unsigned int val);
    stringbuilder& arg(long int val);
    stringbuilder& arg(unsigned long int val);
    stringbuilder& arg(long long int val);
    stringbuilder& arg(unsigned long long int val);
    stringbuilder& arg(char val);
    stringbuilder& arg(const char* val);
    stringbuilder& arg(double val);

    const char* buffer();
    char* moved_buffer();

private:
    stringbuilder(stringbuilder&&);
    stringbuilder(const stringbuilder&);
    stringbuilder& operator=(const stringbuilder&);
    template <class T>
    friend int append_to_buffer(T val, stringbuilder* sb);

    x::stringbuf buf_;
    x::impl::stringfmt fmt_;
};

}

#endif // LIBX_STRING_STRINGBUILDER_H
