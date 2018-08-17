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

private:
    stringbuilder(stringbuilder&&);
    stringbuilder(const stringbuilder&);
    stringbuilder& operator=(const stringbuilder&);

    x::stringbuf buf_;
    x::impl::stringfmt fmt_;
};

}

#endif // LIBX_STRING_STRINGBUILDER_H
