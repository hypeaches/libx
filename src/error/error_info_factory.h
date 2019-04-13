#ifndef LIBX_ERROR_INFO_FACTORY_H
#define LIBX_ERROR_INFO_FACTORY_H

namespace x{

class ErrorInfoImpl;

class ErrorInfoFactory
{
public:
    static ErrorInfoImpl* Create();
};

}

#endif