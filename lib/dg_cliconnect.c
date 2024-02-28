#include "../heders/unp.h"

void dg_cliconnect(FILE *fp, int sockfd, const SA *psevaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE];

    Connect(sockfd, (SA *) psevaddr, servlen);

    while(Fgets(sendline, MAXLINE, fp) != NULL)
    {
        Write(sockfd, sendline, strlen(sendline));
        n = Read(sockfd, recvline, MAXLINE);
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }
}
