#ifndef READN_H
#define READN_H
#include <sys/socket.h>

ssize_t Readn(int fd, void *ptr, size_t nbytes);

#endif
