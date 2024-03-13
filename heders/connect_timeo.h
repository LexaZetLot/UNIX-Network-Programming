#ifndef CONNECT_TIMEO_H
#define CONNECT_TIMEO_H
#include <sys/socket.h>
#ifndef SA
#define SA struct sockaddr
#endif

int connect_timeo(int sockfd, const SA *saptr, socklen_t salen, int nsec);

#endif
