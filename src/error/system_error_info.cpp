#include "system_error_info.h"
#include <system_error>

namespace x{

SystemErrorInfo::SystemErrorInfo(int err_code, const char* msg)
{
    std::error_code ec = std::make_error_code(static_cast<std::errc>(err_code));
    msg_ = std::string(msg) + ". system error code:" + std::to_string(err_code) + ". system error msg:" + ec.message();
}

SystemErrorInfo::~SystemErrorInfo()
{

}

const char* SystemErrorInfo::ToCString()
{
    return msg_.c_str();
}

}
