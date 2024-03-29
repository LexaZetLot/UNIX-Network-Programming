#include "../heders/error.h"
#include "../heders/unp.h"

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;
again:
    if ((n = accept(fd, sa, salenptr)) < 0)
    {
#ifdef EPROTO
        if (errno == EPROTO || errno == ECONNABORTED)
#else
        if (errno == ECONNABORTED)
#endif
            goto again;
        else
            err_sys("accept error");
    }
    return n;
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
        err_sys("bind error");
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (connect(fd, sa, salen) < 0)
        err_sys("connect error");
}

void Getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    if (getpeername(fd, sa, salenptr) < 0)
        err_sys("getpeername error");
}

void Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    if (getsockname(fd, sa, salenptr) < 0)
        err_sys("getsockname error");
}

void Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr)
{
    if(getsockopt(fd, level, optname, optval, optlenptr) < 0)
        err_sys("getsockopt error");
}

#ifdef CONFIG_INET6_RTH_INIT
int Inet6_rth_space(int type, int segments)
{
    int ret;
    ret = inet6_rth_space(type, segments);
    if (ret < 0)
        err_quit("inet6_rth_space error");

    return ret;
}

void * Inet6_rth_init(void *rthbuf, socklen_t rthlen, int type, int segments)
{
    void *ret;

    ret = inet6_rth_init(rthbuf, rthlen, type, segments);
    if (ret == NULL)
        err_quit("inet6_rth_init error");

    return ret;
}

void Inet6_rth_add(void *rthbuf, const struct in6_addr *addr)
{
    if (inet6_rth_add(rthbuf, addr) < 0)
        err_quit("inet6_rth_add error");
}

void Inet6_rth_reverse(vonst void *in, void *out)
{
    if (inet6_rth+reverse(in, out) < 0)
        err_quit("inet6_rth_reverse error");
}

int Inet6_rth_segments(const void *rthbuf)
{
    int ret;

    ret = inet6_rth_segments(rthbuf);
    if (ret < 0)
        err_quit("inet6_rth_segments error");

    return ret;
}

struct in6_addr * Inet6_rth_getaddr(const void *rthbuf, int idx)
{
    struct in6_addr, *ret;

    ret =inte6_rth_getaddr(rthbuf, idx);
    if(ret == NULL)
        err_quit("inet6_rth_getaddr error");

    return 0;
}
#endif

#ifdef CONFIG_KQUEUE
int Kqueue(void)
{
    int ret;
    if((ret = kqueue()) < 0)
        err_sys("kqueue error");

    return ret;
}

int Kevent(int kq, const struct kevent *changelist, int nchanges, struct kevent *eventlist, int nevents, const struct timespec *timeout)
{
    int ret;

    if((ret = kevent(kq, changelist, nchanges, eventlist, nevents, timeout)) < 0)
        err_sys("kevent error");

    return ret;
}
#endif

void Listen (int fd, int backlog)
{
    char *ptr;

    if((ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);
    if(listen(fd, backlog) < 0)
        err_sys("listen error");
}

#ifdef CONFIG_IRQ_POLL
int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout)
{
    int n;

    if ((n = poll(fdarray, nfds, timeout)) < 0)
        err_sys("poll error");

    return n;
}
#endif

ssize_t Recv(int fd, void *ptr, size_t nbytes, int flag)
{
    ssize_t n;
    if ((n = recv(fd, ptr, nbytes, flag)) < 0)
        err_sys("recv error");

    return n;
}

ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags, struct sockaddr *sa, socklen_t *salenptr)
{
    ssize_t n;
    if ((n = recvfrom(fd, ptr, nbytes, flags, sa, salenptr)) < 0)
        err_sys("recvfrom error");

    return n;
}

ssize_t Recvmsg(int fd, struct msghdr *msg, int flags)
{
    ssize_t n;

    if((n = recvmsg(fd, msg, flags)) < 0)
        err_sys("recvmsg error");

    return n;
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
    int n;
    if((n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
        err_sys("selest error");

    return n;
}

void Send(int fd, const void *ptr, size_t nbytes, int flags)
{
    if(send(fd, ptr, nbytes, flags) != (ssize_t)nbytes)
        err_sys("send error");
}

void Sendto (int fd, const void *ptr, size_t nbytes, int flags, const struct sockaddr *sa, socklen_t salen)
{
    if(sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t)nbytes)
        err_sys("sendto error");
}

void Sendmsg(int fd, const struct msghdr *msg, int flags)
{
    unsigned int i;
    ssize_t nbytes;

    nbytes = 0;
    for(i = 0; i < msg->msg_iovlen; i++)
        nbytes += msg->msg_iov[i].iov_len;

    if(sendmsg(fd, msg, flags) != nbytes)
        err_sys("sendmsg error");
}

void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen)
{
    if(setsockopt(fd, level, optname, optval, optlen) < 0)
        err_sys("setsockopt error");
}

void Shutdown(int fd, int how)
{
    if (shutdown(fd, how) < 0)
        err_sys("shutdown error");
}

int Sockatmark(int fd)
{
    int n;

    if((n = sockatmark(fd)) < 0)
        err_sys("sockatmark error");

    return n;
}

int Socket (int family, int type, int protocol)
{
    int n;

    if ((n = socket(family, type, protocol)) < 0)
        err_sys("socket error");

    return n;
}

void Socketpair(int family, int type, int protocol, int *fd)
{
    int n;

    if ((n = socketpair(family, type, protocol, fd)) < 0)
        err_sys("socketpair error");
}
