#ifndef LIBXREDIS_REDIS_LOG_H
#define LIBXREDIS_REDIS_LOG_H

#ifndef XREDISLOG_FATAL
#define XREDISLOG_FATAL(ip, port, errmsg, cmd) printf("redis msg:%s|%d|%s|%s\n", ip, port, errmsg, cmd)
#endif

#ifndef XREDISLOG_WARNING
#define XREDISLOG_WARNING(ip, port, errmsg, cmd) printf("redis msg:%s|%d|%s|%s\n", ip, port, errmsg, cmd)
#endif

#ifndef XREDISLOG_INFO
#define XREDISLOG_INFO(ip, port, errmsg, cmd) printf("redis msg:%s|%d|%s|%s\n", ip, port, errmsg, cmd)
#endif

#ifndef XREDISLOG_DEBUG
#define XREDISLOG_DEBUG(ip, port, errmsg, cmd) printf("redis msg:%s|%d|%s|%s\n", ip, port, errmsg, cmd)
#endif

#endif
