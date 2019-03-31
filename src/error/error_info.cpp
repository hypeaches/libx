#include "x/error/error_info.h"
#include "x/error/xerror.h"
#include <system_error>


namespace x{

namespace
{
const char* default_error_msg = "ok";

void DestroyError(x::XError*& err)
{
    if (err)
    {
        delete err;
        err = nullptr;
    }
}
}

ErrorInfo::ErrorInfo()
{
    err_ = nullptr;
}

ErrorInfo::ErrorInfo(XError* err)
{
    err_ = err;
}

ErrorInfo::ErrorInfo(ErrorInfo&& other)
{
    err_ = other.err_;
    other.err_ = nullptr;
}

ErrorInfo& ErrorInfo::operator=(ErrorInfo&& other)
{
    DestroyError(err_);
    err_ = other.err_;
    return *this;
}

ErrorInfo::~ErrorInfo()
{
    DestroyError(err_);
}

ErrorInfo::operator bool() const
{
    return err_ != nullptr;
}

const char* ErrorInfo::ToCString()
{
    const char* msg = err_ ? err_->ToCString() : default_error_msg;
    return msg;
}

}