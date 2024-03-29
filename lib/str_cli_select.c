#include "../heders/unp.h"

void str_cli_select(FILE *fp, int sockfd)
{
    int maxfdp1, stdineof;
    fd_set rset;
    char buf[MAXLINE];
    int n;

    stdineof = 0;
    FD_ZERO(&rset);
    for(;;)
    {
        if(stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset))                            /* сокет готов для чтения */
        {
            if((n = Readn(sockfd, buf, MAXLINE)) == 0)
            {
                if (stdineof == 1)
                    return;                                     /* нормальное завершения */
                else
                    err_quit("str_cli server terminated prematurely");
            }
            Write(fileno(stdout), buf, n);
        }

        if(FD_ISSET(fileno(fp), &rset))                         /* есть дынные на входе */
        {
            if((n = Read(fileno(fp), buf, MAXLINE)) == 0)
            {
                stdineof = 1;
                Shutdown(sockfd, SHUT_WR);                      /* отправка сегмента FIN */
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            Writen(sockfd, buf, n);
        }
    }
}
