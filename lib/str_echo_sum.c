#include "../heders/unp.h"

void str_echo_sum(int sockfd)
{
    long arg1, arg2;
    ssize_t n;
    char line[MAXLINE];

    for(;;)
    {
        if((n = Readline(sockfd, line, MAXLINE)) == 0)
            return;                         /* соединение закрывается удаленным концом */

        if(sscanf(line, "%ld%ld", &arg1, &arg2) == 2)
            snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
        else
            snprintf(line, sizeof(line), "input error\n");

        n = strlen(line);
        Write(sockfd, line, n);
    }
}
