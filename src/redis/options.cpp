#include "x/redis/options.h"

namespace x{namespace redis{

options::options()
{
    retry_times = 3;
    connect_timeout = 1000;
    read_write_timeout = 1000;
    pool_max_connections = 1;
    pool_max_connections = 5;
}

}}