#ifndef GETNAMEINFO_TIMEO_H
#define GETNAMEINFO_TIMEO_H
#include <sys/socket.h>

int getnameinfo_timeo(const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *serv, size_t servlen, int flags, int time, char * buf, size_t bufsize, int fd);

#endif
