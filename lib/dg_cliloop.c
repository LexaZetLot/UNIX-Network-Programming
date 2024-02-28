#include "../heders/unp.h"

#define NDG 2000                    /* количество дейтаграм для отправки */
#define DGLEN 1400                  /* длина каждой дейтаграм */

void dg_cliloop(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    char sendline[DGLEN];

    for(int i = 0; i < NDG; i++)
    {
        Sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);
    }
}
