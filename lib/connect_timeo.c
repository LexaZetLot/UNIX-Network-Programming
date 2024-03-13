#include "../heders/unp.h"
#include <asm-generic/errno.h>

static void connect_alarm(int signo);

int connect_timeo(int sockfd, const SA *saptr, socklen_t salen, int nsec)
{
    Sigfunc *sigfunc;
    int n;

    sigfunc = Signal(SIGALRM, connect_alarm);
    if(alarm(nsec) != 0)
        err_msg("connect_timeo: alarm was already set");

    if((n = connect(sockfd, saptr, salen)) < 0)
    {
        Close(sockfd);
        if(errno == EINTR)
            errno = ETIMEDOUT;
    }
    alarm(0);                       /* отключение alarm */
    Signal(SIGALRM, sigfunc);       /* восстанавливаем прежний обработчик сигнала */

    return (n);
}

static void connect_alarm(int signo)
{
    return;                         /* простое прерывание connect */
}
