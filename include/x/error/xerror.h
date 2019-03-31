#ifndef LIBX_TASK_XERROR_H
#define LIBX_TASK_XERROR_H

namespace x{

class XError
{
public:
    virtual ~XError() {}
    virtual const char* ToCString() = 0;
};

}

#endif