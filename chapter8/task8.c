#include "../heders/unp.h"
#include <asm-generic/socket.h>

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int n, size = 100000;
    char sendline[65507], recvline[65507 + 1];

    Setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size));
    Setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
    while (Fgets(sendline, MAXLINE, fp) != NULL)
    {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

        recvline[n] = 0;	/* null terminate */
        Fputs(recvline, stdout);
    }
}
