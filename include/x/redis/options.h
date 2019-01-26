#ifndef LIBXREDIS_OPTIONS_H
#define LIBXREDIS_OPTIONS_H

namespace x{namespace redis{

struct options
{
options();

int retry_times;
int connect_timeout;
int read_write_timeout;
int pool_connections;
int pool_max_connections;
};

}}

#endif