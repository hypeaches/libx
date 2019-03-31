#ifndef LIBX_ERROR_ERROR_INFO_H
#define LIBX_ERROR_ERROR_INFO_H

namespace x {

class XError;

class ErrorInfo
{
public:
    ErrorInfo();
    ErrorInfo(XError* err);
    ErrorInfo(ErrorInfo&& other);
    ErrorInfo(const ErrorInfo& other) = delete;
    ErrorInfo& operator=(ErrorInfo&& other);
    ErrorInfo& operator=(const ErrorInfo& other) = delete;
    ~ErrorInfo();

    operator bool() const;
    const char* ToCString();

private:
    x::XError* err_;
};

}

#endif