#ifndef DG_CLIADDR_H
#define DG_CLIADRR_H
#include <sys/socket.h>
#include <stdio.h>
#ifndef SA
#define SA struct sockaddr
#endif

void dg_cliaddr(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);

#endif
