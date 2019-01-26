#include "x/redis/command_helper.h"

#include <hiredis.h>

#include "x/redis/log.h"
#include "x/redis/command.h"
#include "x/redis/connection.h"
#include "x/redis/connection_pool_group.h"

namespace x{namespace redis{

command_helper::command_helper()
{
    reply = NULL;
    conn = connection_pool_group::instance()->create_connection(index);
}

command_helper::~command_helper()
{
    if (reply)
    {
        freeReplyObject(reply);
        reply = NULL;
    }
    connection_pool_group::instance()->release_connection(conn, index);
}

bool command_helper::doexec(const char* cmd)
{
    if (reply)
    {
        freeReplyObject(reply);
        reply = NULL;
    }
    reply = static_cast<redisReply*>(redisCommand(conn->context(), cmd));
    if (!reply)
    {
        XREDISLOG_WARNING(
            conn->host(),
            conn->port(),
            "none redis reply",
            cmd
        );
        return false;
    }
    if (reply->type == REDIS_REPLY_ERROR)
    {
        XREDISLOG_WARNING(
            conn->host(),
            conn->port(),
            "redis replied error",
            cmd
        );
        return false;
    }
    return true;
}

int command_helper::parse_none(std::nullptr_t)
{
    return command::exec_ok;
}

int command_helper::parse_llint(long long int& rep)
{
    int ret = command::exec_failed;
    if (reply && (REDIS_REPLY_INTEGER == reply->type))
    {
        rep = reply->integer;
        ret = command::exec_ok;
    }
    return ret;
}

int command_helper::parse_string(std::string& rep)
{
    int ret = command::exec_failed;
    if (reply && (REDIS_REPLY_STRING == reply->type))
    {
        rep = reply->str;
        ret = command::exec_ok;
    }
    return ret;
}

int command_helper::parse_multistring(std::vector<std::string>& rep)
{
    return command::exec_failed;
}

}}