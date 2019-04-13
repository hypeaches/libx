#include "error_info_factory.h"
#include "error_info_impl.h"

namespace x{

namespace {

thread_local x::ErrorInfoImpl g_error_info_impl;

}

ErrorInfoImpl* ErrorInfoFactory::Create()
{
    ErrorInfoImpl* impl = &g_error_info_impl;
    return impl;
}

}