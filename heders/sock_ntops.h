#ifndef SOCK_NTOPS_H
#define SOCK_NTOPS_H
#include <sys/socket.h>

char *Sock_ntop(const struct sockaddr *sa, socklen_t salen);

#endif
