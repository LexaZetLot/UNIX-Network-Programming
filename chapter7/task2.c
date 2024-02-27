#include "../heders/unp.h"
#include <netinet/in.h>
#include <sys/socket.h>

int main (int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    socklen_t len = 4;
    int buf;

    if (argc != 2)
        err_quit ("usage: a.out <IPaddress>");
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); /* сервер времени и даты*/

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", argv[1]);


    getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &buf, &len);
    printf("RCVBUF: %d\n", buf);
#ifdef TCP_MAXSEG
    getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &buf, &len);
    printf("RCVBUF: %d\n", buf);
#endif
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");
    getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &buf, &len);
    printf("RCVBUF: %d\n", buf);
#ifdef TCP_MAXSEG
    getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &buf, &len);
    printf("RCVBUF: %d\n", buf);
#endif

    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0; /* завершающий нуль*/
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }

    if (n < 0)
        err_sys("read error");

    exit (0);
}
