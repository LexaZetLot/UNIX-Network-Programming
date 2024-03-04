#ifndef SCTP_ADDRESS_TO_ASSOCID_H
#define SCTP_ADDRESS_TO_ASSOCID_H
#include <sys/socket.h>
#include <netinet/sctp.h>

sctp_assoc_t sctp_address_to_associd(int sock_fd, struct sockaddr *sa, socklen_t salen);

#endif
