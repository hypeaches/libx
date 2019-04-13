#ifndef LIBX_ERROR_INFO_IMPL_H
#define LIBX_ERROR_INFO_IMPL_H

#include <string>
#include "x/error/error_info.h"

namespace x{

class ErrorInfoImpl : public x::ErrorInfo
{
public:
    ErrorInfoImpl();
    virtual ~ErrorInfoImpl();

    virtual const char* Ip() override;
    virtual int Port() override;
    virtual int SystemErrorCode() override;
    virtual const char* Message() override;

    void SetSystemError(int ec, const char* mymsg);
    void SetNetworkError(const char* ip, int port, const char* mymsg);
    void SetSystemNetworkError(int err_no, const char* ip, int port, const char* mymsg);

private:
    void clear();

private:
    std::string ip_;
    int port_;
    int system_error_code_;
    std::string msg_;
};

}

#endif