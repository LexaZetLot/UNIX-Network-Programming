#ifndef HOST_SERV_H
#define HOST_SERV_H

struct addrinfo *host_serv(const char *host, const char *serv, int family, int socktype);

#endif
