#include "../heders/unp.h"
#include "../heders/sum.h"

void str_cli_bit(FILE *fp, int sockfd)
{
    char sendline[MAXLINE];
    struct args args;
    struct result result;

    while(Fgets(sendline, MAXLINE, fp) != NULL)
    {
        if(sscanf(sendline, "%ld%ld", &args.arg1, &args.arg2) != 2)
        {
            printf("invalib input, %s", sendline);
            continue;
        }
        Writen(sockfd, &args, sizeof(args));
        if(Readn(sockfd, &result, sizeof(result)) == 0)
            err_quit("str_cli: server terminated prematurely");

        printf("%ld\n", result.sum);
    }
}
