#ifndef DG_CLICONNECT_H
#define DG_CLICONNECT_H
#include <sys/socket.h>
#include <stdio.h>
#ifndef SA
#define SA struct sockaddr
#endif

void dg_cliconnect(FILE *fp, int sockfd, const SA *psevaddr, socklen_t servlen);

#endif
