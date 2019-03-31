#ifndef LIBX_SYSTEM_ERROR_INFO_H
#define LIBX_SYSTEM_ERROR_INFO_H

#include <string>
#include "x/error/xerror.h"

namespace x{

class SystemErrorInfo : public x::XError
{
public:
    SystemErrorInfo(int ec, const char* msg);
    virtual ~SystemErrorInfo();

    virtual const char* ToCString() override;

private:
    std::string msg_;
};

}

#endif