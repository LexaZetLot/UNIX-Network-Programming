#include "../heders/unp.h"
#include <time.h>
#define MAXSOCKADDR 128


int main(int argc, char **argv)
{
    socklen_t len;
    struct sockaddr *cliaddr;
    char buff[MAXLINE];
    time_t ticks;

    daemon_inetd(argv[0], 0);
    cliaddr = Malloc(MAXSOCKADDR);
    len = MAXSOCKADDR;
    Getpeername(0, cliaddr, &len);
    err_msg("connrction from %s", Sock_ntop(cliaddr, len));

    ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%.24s\n", ctime(&ticks));
    Write(0, buff, strlen(buff));

    Close(0);                   /* закрываем соединение TCP */
    exit(0);

}
