#ifndef LIBXREDIS_CONNECTION_POOL_H
#define LIBXREDIS_CONNECTION_POOL_H

#include <vector>
#include <string>

namespace x{namespace redis{

struct options;
class connection;

class connection_pool
{
public:
    ~connection_pool();
    bool init(const std::string& host, int port, const options* opt);
    connection* create();
    void release(connection* conn);
    void increase();

private:
    int real_size_;
    int port_;
    std::string host_;
    const options* opt_;
    std::vector<connection*> pool_;
};

}}

#endif