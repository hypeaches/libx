#ifndef LIBXREDIS_COMMAND_H
#define LIBXREDIS_COMMAND_H

#include <string>
#include <vector>

namespace x{namespace redis{

struct options;

class command
{
public:
    command();
    ~command();

public:
    enum {
        exec_ok = 0,
        exec_null,
        exec_failed
    };
    static void init(const options* opt);
    static bool add_pool(const char* host, int port);

public:
    int exec(const std::string& cmd);
    int exec(const std::string& cmd, std::string& rep);
    int exec(const std::string& cmd, long long int& rep);
    int exec(const std::string& cmd, std::vector<std::string>& rep);
    int exec(const std::vector<std::string>& cmds, int limit);
    int exec(const std::vector<std::string>& cmds, int limit, std::vector<std::string>& rep);
};

}}

#endif
