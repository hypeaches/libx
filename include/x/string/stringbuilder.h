#ifndef LIBX_STRING_STRINGBUILDER_H
#define LIBX_STRING_STRINGBUILDER_H

#include "x/string/impl/stringfmt.h"

namespace x {

class stringbuilder {
public:
    stringbuilder();
    stringbuilder(int buflen);
    ~stringbuilder();

    void test();
private:
    stringbuilder(stringbuilder&&);
    stringbuilder(const stringbuilder&);
    stringbuilder& operator=(const stringbuilder&);

    char* buf_;
    int buf_max_size_;
    x::impl::stringfmt fmt_;
};

}

#endif // LIBX_STRING_STRINGBUILDER_H
