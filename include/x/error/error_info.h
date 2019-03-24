#ifndef LIBX_ERROR_ERROR_INFO_H
#define LIBX_ERROR_ERROR_INFO_H

#include <string>

namespace x {

struct ErrorInfo
{
    static std::string ToString(int ec);
};

}

#endif