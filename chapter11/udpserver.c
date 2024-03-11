#include "../heders/unp.h"
#include <time.h>

int main(int argc, char **argv)
{
    int sockfd;
    ssize_t n;
    char buff[MAXLINE];
    time_t ticks;
    socklen_t addrlen, len;
    struct sockaddr_storage cliaddr;

    if(argc == 2)
        sockfd = Udp_server(NULL, argv[1], &addrlen);
    else if(argc == 3)
        sockfd = Udp_server(argv[1], argv[2], &addrlen);
    else
        err_quit("usage: daytimrudpsrv [<host>] <service or port>");

    for(;;)
    {
        len = sizeof(cliaddr);
        n = Recvfrom(sockfd, buff, MAXLINE, 0, (SA *)&cliaddr, &len);
        printf("datagram from %s\n", Sock_ntop((SA*)&cliaddr, len));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%24s\n", ctime(&ticks));
        Sendto(sockfd, buff, strlen(buff), 0, (SA *)&cliaddr, len);
    }
}