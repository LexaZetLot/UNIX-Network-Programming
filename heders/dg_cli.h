#ifndef DG_CLI_H
#define DG_CLI_H
#include <sys/socket.h>
#include <stdio.h>
#ifndef SA
#define SA struct sockaddr
#endif

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);

#endif
