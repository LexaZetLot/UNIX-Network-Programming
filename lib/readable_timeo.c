#include "../heders/unp.h"

int readable_timeo(int fd, int sec)
{
    fd_set rset;
    struct timeval tv;

    FD_ZERO(&rset);
    FD_SET(fd, &rset);

    tv.tv_sec = sec;
    tv.tv_usec = 0;

    return (select(fd + 1, &rset, NULL, NULL, &tv));
    /* > если дескриптор готов для чтения */
}

int Readable_time(int fd, int sec)
{
    int n;
    if((n = readable_timeo(fd, sec)) < 0)
        err_sys("readable_timr error");
    return (n);
}
