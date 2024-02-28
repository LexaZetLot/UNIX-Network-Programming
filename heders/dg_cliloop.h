#ifndef DG_CLILOOP_H
#define DG_CLILOOP_H
#include <sys/socket.h>
#include <stdio.h>
#ifndef SA
#define SA struct sockaddr
#endif

void dg_cliloop(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);

#endif
