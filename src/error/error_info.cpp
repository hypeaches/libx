#include "x/error/error_info.h"
#include "error_info_factory.h"
#include "error_info_impl.h"


namespace x{

x::ErrorInfo::~ErrorInfo()
{}

x::ErrorInfo* x::ErrorInfo::GetErrorInfo()
{
    return x::ErrorInfoFactory::Create();
}

}