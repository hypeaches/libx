#ifndef LIBX_ERROR_ERROR_INFO_H
#define LIBX_ERROR_ERROR_INFO_H

namespace x {

class ErrorInfo
{
public:
    static x::ErrorInfo* GetErrorInfo();

    virtual ~ErrorInfo();
    virtual const char* Ip() = 0;
    virtual int Port() = 0;
    virtual int SystemErrorCode() = 0;
    virtual const char* Message() = 0;
};

}

#endif