#include "error_info_impl.h"
#include <system_error>

namespace x{

ErrorInfoImpl::ErrorInfoImpl()
{
    msg_.reserve(2048);
    clear();
}

ErrorInfoImpl::~ErrorInfoImpl()
{

}

const char* ErrorInfoImpl::Ip()
{
    return ip_.c_str();
}

int ErrorInfoImpl::Port()
{
    return port_;
}

int ErrorInfoImpl::SystemErrorCode()
{
    return system_error_code_;
}

const char* ErrorInfoImpl::Message()
{
    return msg_.c_str();
}

void ErrorInfoImpl::SetSystemError(int err_no, const char* mymsg)
{
    clear();
    system_error_code_ = err_no;
    std::error_code ec = std::make_error_code(static_cast<std::errc>(err_no));
    msg_.append(mymsg)
        .append(". error code: ").append(std::to_string(err_no))
        .append(". error msg: ").append(ec.message());
}

void ErrorInfoImpl::SetNetworkError(const char* ip, int port, const char* mymsg)
{
    clear();
    ip_ = ip;
    port_ = port;
    msg_.append(mymsg)
        .append(". ip: ").append(ip)
        .append(". port: ").append(std::to_string(port));
}

void ErrorInfoImpl::SetSystemNetworkError(int err_no, const char* ip, int port, const char* mymsg)
{
    clear();
    ip_ = ip;
    port_ = port;
    system_error_code_ = err_no;
    std::error_code ec = std::make_error_code(static_cast<std::errc>(err_no));
    msg_.append(mymsg)
        .append(". ip: ").append(ip)
        .append(". port: ").append(std::to_string(port))
        .append(". error code: ").append(std::to_string(err_no))
        .append(". error msg: ").append(ec.message());
}

void ErrorInfoImpl::clear()
{
    ip_.clear();
    port_ = 0;
    system_error_code_ = 0;
    msg_.clear();
}

}
