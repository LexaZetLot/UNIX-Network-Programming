#include "../heders/unp.h"
#include <stdio.h>

void str_echo(int sockfd)
{
    FILE *fp;
    fp = fopen("log.txt", "w+r");
    ssize_t n;
    char buf[MAXLINE];

    /*while (true)
    {*/
    again:
        while((n = read(sockfd, buf, MAXLINE)) > 0)
        {
            fputs("sss", fp);
            //Writen(sockfd, buf, n);
        }
        if(n < 0 && errno == EINTR)
            goto again;
        else if(n < 0)
            err_sys("str_echo: read error");
    /*}*/
}
