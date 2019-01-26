#ifndef LIBXREDIS_CONNECTION_POOL_GROUP_H
#define LIBXREDIS_CONNECTION_POOL_GROUP_H

namespace x{namespace redis{

struct options;
class connection;
class connection_pool;

class connection_pool_group {
public:
    ~connection_pool_group();
    static connection_pool_group* instance();
    const options* option();
    void init(const options* opt);
    bool add_pool(const char* host, int port);
    connection* create_connection(int& pool_index);
    void release_connection(connection* conn, int pool_index);

private:
    connection_pool_group();
    connection_pool_group(connection_pool_group&&);
    connection_pool_group(const connection_pool_group&);
    connection_pool_group& operator=(connection_pool_group&&);
    connection_pool_group& operator=(const connection_pool_group&);

    bool init_group();
};

}}

#endif