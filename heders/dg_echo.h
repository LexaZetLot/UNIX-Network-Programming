#ifndef DG_ECHO_H
#define DG_ECHO_H
#include <sys/socket.h>
#ifndef SA
#define SA struct sockaddr
#endif

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen);

#endif
