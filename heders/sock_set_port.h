#ifndef SOCK_SET_PORT_H
#define SOCK_SET_PORT_H
#include <sys/socket.h>

void sock_set_port(struct sockaddr *sa, socklen_t salen, int port);

#endif
