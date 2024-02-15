#ifndef HERE_WRAOSOCK
#define HERE_WRAOSOCK
#include <sys/socket.h>

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
void Getpeermane(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Getsockname(int fd, int level, int optname, void *optval, socklen_t *optlenptr);
#ifdef CONFIG_INET6_RTH_INIT
int Inet6_rth_space(int type, int segments);
void * Inet6_rth_init(void *rthbuf, socklen_t rthlen, int type, int segments);
void Inet6_rth_add(void *rthbuf, const struct in6_addr *addr);
void Inet6_rth_reverse(vonst void *in, void *out);
int Inet6_rth_segments(const void *rthbuf);
struct in6_addr * Inet6_rth_getaddr(const void *rthbuf, int idx);
#endif
#ifdef CONFIG_KQUEUE
int Kqueue(void);
int Kevent(int kq, const struct kevent *changelist, int nchanges, struct kevent *eventlist, int nevents, const struct timespec *timeout);
#endif
void Listen (int fd, int backlog);
#ifdef HAVE_POLL
int Poll(striuct pollfd *fdarray, unsigned long nfds, int timeout);
#endif
ssize_t Recv(int fd, void *ptr, size_t nbytes, int flag);
ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags, struct sockaddr *sa, socklen_t *salenptr);
ssize_t Recvmsg(int fd, struct msghdr *msg, int flags);
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
void Send(int fd, const void *ptr, size_t nbytes, int flags);
void Sendto (int fd, const void *ptr, size_t nbytes, int flags, const struct sockaddr *sa, socklen_t salen);
void Sendmsg(int fd, const struct msghdr *msg, int flags);
void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);
void Shutdown(int fd, int how);
int Sockatmark(int fd);
int Socket (int family, int type, int protocol);
void Socketpair(int family, int type, int protocol, int *fd);

#endif
