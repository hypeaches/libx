#include "x/redis/command.h"

#include <hiredis.h>

#include "x/redis/log.h"
#include "x/redis/options.h"
#include "x/redis/command_helper.h"
#include "x/redis/connection_pool_group.h"

namespace x{namespace redis{

namespace{

template <class ReplyType, class CallbackType>
int doexec(const std::string& cmd, ReplyType& rep, const CallbackType& cb)
{
    int ret = command::exec_failed;
    const options* opt = connection_pool_group::instance()->option();
    for (int i = 0; (command::exec_failed == ret) && (i < opt->retry_times); i++)
    {
        command_helper helper;
        if (!helper.conn)
        {
            continue;
        }
        if (!helper.doexec(cmd.c_str()))
        {
            continue;
        }
        ret = (helper.*cb)(rep);
    }
    return ret;
}

}

command::command()
{
}

command::~command()
{
}

void command::init(const options* opt)
{
    connection_pool_group::instance()->init(opt);
}

bool command::add_pool(const char* host, int port)
{
    return connection_pool_group::instance()->add_pool(host, port);
}

int command::exec(const std::string& cmd)
{
    std::nullptr_t ptr;
    return doexec(cmd, ptr, &command_helper::parse_none);
}

int command::exec(const std::string& cmd, std::string& rep)
{
    return doexec(cmd, rep, &command_helper::parse_string);
}

int command::exec(const std::string& cmd, long long int& rep)
{
    return doexec(cmd, rep, &command_helper::parse_llint);
}

int command::exec(const std::string& cmd, std::vector<std::string>& rep)
{
    return doexec(cmd, rep, &command_helper::parse_multistring);
}

int command::exec(const std::vector<std::string>& cmds, int limit)
{
    return command::exec_failed;
}

int command::exec(const std::vector<std::string>& cmds, int limit, std::vector<std::string>& rep)
{
    return command::exec_failed;
}

}}
