#ifndef SCTP_STRCLIECHO_H
#define SCTP_STRCLIECHO_H
#include <sys/socket.h>
#include <stdio.h>

void sctpstr_cli_echoall(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen);

#endif
