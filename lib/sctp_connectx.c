#include "../heders/unp.h"

#ifdef GO_SCTP_CONNECTX_C
#define __SYMPFX(pfx, sym) #pfx sym
#define _SYMPFX(pfx, sym) __SYMPFX(pfx, sym)
#define SYMPFX(sym) _SYMPFX(__USER_LABEL_PREFIX, #sym)

#if HAVE_ATTRIBUTE_SYMVER
#define SYMER(name, name2) __attribute__ ((symver (SYMPFX(name2))))
#else
#define SYMVER(name, name2) __asm__(".symver " SYMPFX(name) "," SYMPFX(name2));
#endif

static int __connectx_addrsize(const struct sockaddr *addrs, const int addrcnt)
{
    const char *addrbuf;
    const struct sockaddr *sa_addr;
    int addrs_size = 0;
    int i;

    addrbuf = (char *)addrs;
    for(i = 0; i < addrcnt; i++)
    {
        sa_addr = (const struct sockaddr *)addrbuf;
        switch(sa_addr->sa_family)
        {
            case AF_INET:
                addrs_size += sizeof(struct sockaddr_in);
                addrbuf += sizeof(struct sockaddr_in);
                break;
            case AF_INET6:
                addrs_size += sizeof(struct sockaddr_in6);
                addrbuf += sizeof(struct sockaddr_in6);
                break;
            default:
                errno = EINVAL;
                return -1;
        }
    }
    return addrs_size;
}

SYMVER(__sctp_connectx, __sctp_connectx@)
int __sctp_connectx(int fd, struct sockaddr *addrs, int addrcnt)
{
    int addrs_size = __connectx_addrsize(addrs, addrcnt);

    if(addrs_size < 0)
        return addrs_size;

    return setsockopt(fd, SOL_SCTP, SCTP_SOCKOPT_CONNECTX_OLD, addrs, addrs_size);
}

SYMVER(sctp_connectx_orig, sctp_connectx@VERS_1)
extern int sctp_connectx_orig (int) __attribute((alias("__sctp_connectx")));

static int __connectx(int fd, struct sockaddr *addrs, socklen_t addrs_size, sctp_assoc_t *id)
{
    int status;

    if(id)
        *id = 0;

    status = setsockopt(fd, SOL_SCTP, SCTP_SOCKOPT_CONNECTX, addrs, addrs_size);

    if(status > 0)
    {
        if(id)
            *id = status;
        return 0;
    }
    if(status < 0 && errno != ENOPROTOOPT)
        return status;
    if(id)
    {
        errno = ENOPROTOOPT;
        return -1;
    }

    return setsockopt(fd, SOL_SCTP, SCTP_SOCKOPT_CONNECTX_OLD, addrs, addrs_size);
}

SYMVER(sctp_connectx2, sctp_connectx@VERS_2)
int sctp_connectx2(int fd, struct sockaddr *addrs, int addrcnt, sctp_assoc_t *id)
{
    int addrs_size = __connectx_addrsize(addrs, addrcnt);

    if(addrs_size < 0)
        return addrs_size;

    return __connectx(fd, addrs, addrs_size, id);
}

SYMVER(sctp_connectx3, sctp_connectx@@VERS_3)
int sctp_connectx3(int fd, struct sockaddr *addrs, int addrcnt, sctp_assoc_t *id)
{
    int addrs_size = __connectx_addrsize(addrs, addrcnt);
    int status;
    struct sctp_getaddresses param;
    socklen_t opt_len = sizeof(param);

    if(addrs_size < 0)
        return addrs_size;

    param.sget_assoc_id = 0;
    param.addr->sa.sa_family = addrs_size;
    param.addr->sa = *addrs;
    status = getsockopt(fd, SOL_SCTP, SCTP_SOCKOPT_CONNECTX3, &param, &opt_len);
    if(status == 0 || errno == EINPROGRESS)
        if(id)
            *id = param.sget_assoc_id;
    if(errno != ENOPROTOOPT)
        return status;

    if(id)
    {
        status = fcntl(fd, F_GETFL);
        if(status < 0)
            return status;
        if(status & O_NONBLOCK)
        {
            errno = ENOPROTOOPT;
            return -1;
        }
    }
    return __connectx(fd, addrs, addrs_size, id);
}
#endif
