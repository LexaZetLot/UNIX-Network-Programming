#include "../heders/unp.h"
#include "../heders/sum.h"

void str_echo_bit(int sockfd)
{
    ssize_t n;
    struct args args;
    struct result result;

    for(;;)
    {
        if((n = Readn(sockfd, &args, sizeof(args))) == 0)
            return;             /* соединение закрыто удаленным концом */

        result.sum = args.arg1 + args.arg2;
        Writen(sockfd, &result, sizeof(result));
    }
}
