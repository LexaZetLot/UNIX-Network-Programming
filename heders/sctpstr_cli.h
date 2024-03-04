#ifndef SCTPSTR_CLI_H
#define SCTPSTR_CLI_H
#include <sys/socket.h>
#include <stdio.h>

void sctpstr_cli(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen);

#endif
