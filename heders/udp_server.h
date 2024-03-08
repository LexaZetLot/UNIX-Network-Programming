#ifndef UDP_SERVER_H
#define UDP_SERVER_H
#include <sys/socket.h>

int Udp_server(const char *host, const char *serv, socklen_t *addrlenp);

#endif
