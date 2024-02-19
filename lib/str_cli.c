#include "../heders/unp.h"

void str_cli(FILE *fp, int sockfd)
{
    FILE *f = fopen("logclient.txt", "w+r");
    char sendline [MAXLINE], recvline[MAXLINE];

    //printf("%s", Fgets(sendline, MAXLINE, fp));
    //printf("%s", Fgets(sendline, MAXLINE, fp));
    while (Fgets(sendline, MAXLINE, fp) != NULL)
    {
        Writen(sockfd, sendline, strlen(sendline));
        //puts(sendline);
        printf("*****");

        //if(Readline(sockfd, recvline, MAXLINE) == 0)
        //    err_quit("str_cli: server terminated prematurely");
        fputs(recvline, fp);
/*
        Fputs(recvline, stdout);*/
    }
}
