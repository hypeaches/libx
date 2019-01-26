#include "x/redis/connection.h"
#include <sys/time.h>
#include <hiredis.h>
#include "x/redis/log.h"
#include "x/redis/options.h"

namespace x{namespace redis{

connection::connection()
{
    opt_ = nullptr;
    context_ = nullptr;
}

connection::~connection()
{
    opt_ = nullptr;
    if (context_)
    {
        redisFree(context_);
        context_ = nullptr;
    }
}

bool connection::init(const std::string& host, int port, const options* opt)
{
    opt_ = opt;
    port_ = port;
    host_ = host;
    return true;
}

bool connection::connect()
{
    timeval timeout;
    timeout.tv_sec = opt_->connect_timeout / 1000;
    timeout.tv_usec = opt_->connect_timeout % 1000 * 1000;

    context_ = redisConnectWithTimeout(
        host_.c_str(),
        port_,
        timeout
    );
    if (!context_)
    {
        XREDISLOG_WARNING(
            host_.c_str(),
            port_,
            "connect failed",
            ""
        );
        return false;
    }
    if (context_->err)
    {
        XREDISLOG_WARNING(
            host_.c_str(),
            port_,
            context_->errstr,
            ""
        );
        return false;
    }

    return true;
}

bool connection::disconnect()
{
    if (context_)
    {
        redisFree(context_);
        context_ = nullptr;
    }
    return true;
}

}}