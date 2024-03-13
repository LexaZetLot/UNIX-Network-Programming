#ifndef DG_CLI_ALRM_H
#define DG_CLI_ALRM_H
#include <sys/socket.h>
#include <stdio.h>
#ifndef SA
#define SA struct sockaddr
#endif

void dg_cli_alrm(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);

#endif
