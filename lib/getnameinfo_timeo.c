#include "../heders/unp.h"

int getnameinfo_timeo(const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *serv, size_t servlen, int flags, int time, char * buf, size_t bufsize, int fd)
{
    pid_t f;
    if((f = Fork()) > 0)
    {
        return getnameinfo(sa, salen, host, hostlen, serv, servlen, flags);
    }
    sleep(time);
    inet_ntop(fd, sa, buf, bufsize);
    return -1;
}
