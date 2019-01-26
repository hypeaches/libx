#include "x/redis/connection_pool_group.h"

#include <atomic>
#include <vector>
#include <mutex>

#include "x/redis/options.h"
#include "x/redis/connection.h"
#include "x/redis/connection_pool.h"

namespace x{namespace redis{

namespace {

std::atomic<uint64_t> pool_group_index(0);
const options* global_options;
std::vector<std::pair<std::string, int>> host_group;
thread_local std::vector<connection_pool*> pool_group;

}

connection_pool_group::~connection_pool_group()
{}

connection_pool_group::connection_pool_group()
{}

connection_pool_group::connection_pool_group(connection_pool_group&&)
{}

connection_pool_group::connection_pool_group(const connection_pool_group&)
{}

connection_pool_group& connection_pool_group::operator=(connection_pool_group&&)
{
    return *this;
}

connection_pool_group& connection_pool_group::operator=(const connection_pool_group&)
{
    return *this;
}

connection_pool_group* connection_pool_group::instance()
{
    static connection_pool_group group;
    return &group;
}

const options* connection_pool_group::option()
{
    return global_options;
}

void connection_pool_group::init(const options* opt)
{
    global_options = opt;
}

bool connection_pool_group::add_pool(const char* host, int port)
{
    host_group.push_back(std::make_pair(std::string(host), port));
    return true;
}

connection* connection_pool_group::create_connection(int& pool_index)
{
    init_group();
    uint64_t index = pool_group_index.fetch_add(1);
    uint64_t pool_group_size = static_cast<uint64_t>(pool_group.size());
    pool_index = static_cast<int>(index % pool_group_size);
    connection_pool* pool = pool_group[pool_index];
    connection* conn = pool->create();
    return conn;
}

void connection_pool_group::release_connection(connection* conn, int pool_index)
{
    if (conn)
    {
        pool_group[pool_index]->release(conn);
    }
}

bool connection_pool_group::init_group() {
    if (!pool_group.empty())
    {
        return true;
    }

    connection_pool* pool = nullptr;
    for (const auto& pair : host_group)
    {
        pool = new connection_pool;
        pool->init(pair.first, pair.second, global_options);
        pool_group.push_back(pool);
    }
    return true;
}

}}