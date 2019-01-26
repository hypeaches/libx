#ifndef LIBXREDIS_CONNECTION_H
#define LIBXREDIS_CONNECTION_H

#include <string>

struct redisContext;

namespace x{namespace redis{

struct options;

class connection
{
public:
    connection();
    ~connection();
    bool init(const std::string& host, int port, const options* opt);
    bool connect();
    bool disconnect();
    int port() { return port_; }
    const char* host() { return host_.c_str(); }
    const options* option() { return opt_; }
    redisContext* context() { return context_; }

private:
    int port_;
    std::string host_;
    const options* opt_;
    redisContext* context_;
};

}}

#endif