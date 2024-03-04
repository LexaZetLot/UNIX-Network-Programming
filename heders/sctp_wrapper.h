#ifndef SCTP_WRAPPER_H
#define SCTP_WRAPPER_H
#include <sys/socket.h>
#include <stdint.h>

int Sctp_recvmsg(int s, void *msg, size_t len, struct sockaddr *from, socklen_t *fromlen, struct sctp_sndrcvinfo *sinfo, int *msg_flags);
int Sctp_sendmsg(int s, void *data, size_t len, struct sockaddr *to, socklen_t tolen, uint32_t ppid, uint32_t flags, uint16_t stream_no, uint32_t timetolive, uint32_t context);
int Sctp_bindx(int sock_fd, struct sockaddr *at, int num, int op);

#endif
