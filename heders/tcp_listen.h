#ifndef TCP_LISTEN_H
#define TCP_LISTEN_H
#include <sys/socket.h>

int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);

#endif
