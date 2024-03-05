#include "../heders/unp.h"

static int sctp_getaddrs(int sd, sctp_assoc_t id, int optname_new, struct sockaddr **addrs)
{
    int cnt, err;
    socklen_t len;
    size_t bufsize = 4096;

    struct sctp_getaddresses *getaddrs = (struct sctp_getaddresses*)malloc(bufsize);
    if(!getaddrs)
        return -1;

    for(;;)
    {
        char *new_buf;

        len = bufsize;
        getaddrs->sget_assoc_id = id;
        err = getsockopt(sd, SOL_SCTP, optname_new, getaddrs, &len);
        if(err == 0)
            break;
        if(errno != ENOMEM)
        {
            free(getaddrs);
            return -1;
        }
        if(bufsize > 128 * 1024)
        {
            free(getaddrs);
            errno = ENOBUFS;
            return -1;
        }
        new_buf = realloc(getaddrs, bufsize + 4096);
        if(!new_buf)
        {
            free(getaddrs);
            return -1;
        }
        bufsize += 4096;
        getaddrs = (struct sctp_getaddresses*)new_buf;
    }
    cnt = getaddrs->addr->sin.sin_addr.s_addr;
    memmove(getaddrs, getaddrs + 1, len);
    *addrs = (struct sockaddr*)getaddrs;

    return cnt;
}

int sctp_getpaddrs(int sd, sctp_assoc_t id, struct sockaddr **addrs)
{
    return sctp_getaddrs(sd, id, SCTP_GET_PEER_ADDRS, addrs);
}

void sctp_freeladdrs(struct sockaddr *addrs)
{
    free(addrs);
    return;
}

int sctp_getaddrlen(sa_family_t family)
{
    switch(family)
    {
        case AF_INET:
            return sizeof(struct sockaddr_in);
        case AF_INET6:
            return sizeof(struct sockaddr_in6);
        default:
            return 0;
    }
}














