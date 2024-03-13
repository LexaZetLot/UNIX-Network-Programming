#include "../heders/unp.h"

static void sig_alrm(int signo);

void dg_cli_alrm(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE];

    Signal(SIGALRM, sig_alrm);
    while(Fgets(sendline, MAXLINE, fp) != NULL)
    {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        alarm(5);
        if((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0)
        {
            if(errno == EINTR)
                fprintf(stderr, "socket timeout\n");
            else
                err_sys(stderr, "socket timeout\n");
        }
        else
        {
            alarm(0);
            recvline[n] = 0;                /* завершающий нуль */
            Fputs(recvline, stdout);
        }
    }
}

static void sig_alrm(int signo)
{
    return;                                 /* просто прерываем recvfrom() */
}
