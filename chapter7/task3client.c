#include "../heders/unp.h"
#include <asm-generic/socket.h>

int main(int argc, char **argv)
{
    int sockfd;
    socklen_t len;
    struct linger lin;
    struct sockaddr_in servaddr;
    lin.l_linger = 0;
    lin.l_onoff = 1;

    if(argc != 2)
        err_quit("usage: tcpcli <IPaddress>");

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);             /* эта функция выполняет все необходимые действия со стороны клиента */

    len = sizeof(lin);
    Setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &lin, len);
    exit(0);
}
