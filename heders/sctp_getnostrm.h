#ifndef SCTP_GETNOSTRM_H
#define SCTP_GETNOSTRM_H
#include <sys/socket.h>

int sctp_get_no_strms(int sock_fd, struct sockaddr *to, socklen_t tolen);

#endif
