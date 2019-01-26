#ifndef LIBXREDIS_COMMAND_HELPER_H
#define LIBXREDIS_COMMAND_HELPER_H

#include <string>
#include <vector>

struct redisReply;

namespace x{namespace redis{

class connection;

class command_helper
{
public:
    command_helper();
    ~command_helper();

    bool doexec(const char* cmd);
    int parse_none(std::nullptr_t);
    int parse_llint(long long int& rep);
    int parse_string(std::string& rep);
    int parse_multistring(std::vector<std::string>& rep);

    int index;
    connection* conn;
    redisReply* reply;
};

}}

#endif