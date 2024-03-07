#ifndef SOCK_NTOP_HOST_H
#define SOCK_NTOP_HOST_H
#include <sys/socket.h>

char *Sock_ntop_host(const struct sockaddr *sa, socklen_t salen);

#endif
