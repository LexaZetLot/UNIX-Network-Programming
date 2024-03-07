#include "../heders/unp.h"
#include <time.h>

int main (int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t addrlen, len;
    struct sockaddr_storage cliaddr;
    char buff[MAXLINE];
    time_t ticks;

    if(argc == 2)
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    else if(argc == 3)
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    else
        err_quit("usage: daytimetcpsre2 [<host>] <service or port>");

    for(;;)
    {
        len = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *) &cliaddr, &len);
        printf("conntction fron %s\n", Sock_ntop((SA *) &cliaddr, len));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\n", ctime(&ticks));

        Close(connfd);
    }
}
