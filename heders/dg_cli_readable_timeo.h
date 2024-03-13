#ifndef DG_CLI_READSBLE_TIMEO_H
#define DG_CLI_READSBLE_TIMEO_H
#include <sys/socket.h>
#include <stdio.h>
#ifndef SA
#define SA struct sockaddr
#endif

void dg_cli_readable_timeo(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);

#endif
