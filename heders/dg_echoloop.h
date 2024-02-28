#ifndef DG_ECHOLOOP_H
#define DG_ECHOLOOP_H
#include <sys/socket.h>
#ifndef SA
#define SA struct sockaddr
#endif

void dg_echoloop(int sockfd, SA *pcliaddr, socklen_t clilen);

#endif
