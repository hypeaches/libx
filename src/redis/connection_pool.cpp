#include "x/redis/connection_pool.h"
#include "x/redis/log.h"
#include "x/redis/options.h"
#include "x/redis/connection.h"

namespace x{namespace redis{

connection_pool::~connection_pool()
{
    for (connection* conn : pool_)
    {
        delete conn;
    }
    pool_.clear();
}

bool connection_pool::init(const std::string& host, int port, const options* opt)
{
    opt_ = opt;
    port_ = port;
    host_ = host;
    real_size_ = 0;
    pool_.reserve(opt_->pool_max_connections);
    for (int i = 0; i < opt_->pool_connections; i++)
    {
        increase();
    }
    return true;
}

connection* connection_pool::create()
{
    connection* conn = nullptr;
    if (pool_.empty())
    {
        increase();
    }
    if (!pool_.empty())
    {
        conn = pool_.back();
        pool_.pop_back();
    }
    if (!conn)
    {
        XREDISLOG_WARNING(
            host_.c_str(),
            port_,
            "create connection failed",
            ""
        );
    }
    return conn;
}

void connection_pool::release(connection* conn)
{
    pool_.push_back(conn);
}

void connection_pool::increase()
{
    if (real_size_ < opt_->pool_max_connections)
    {
        connection* conn = new connection;
        conn->init(host_, port_, opt_);
        conn->connect();
        pool_.push_back(conn);
        real_size_++;
    }
}

}}