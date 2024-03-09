#ifndef SOCK_SET_ADDR_H
#define SOCK_SET_ADDR_H
#include <sys/socket.h>

void sock_set_addr(struct sockaddr *sa, socklen_t salen, const void *addr);

#endif
