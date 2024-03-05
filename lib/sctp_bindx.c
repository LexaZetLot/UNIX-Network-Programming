#include "../heders/unp.h"
#include <netinet/in.h>
#include <sys/socket.h>

int sctp_bindx(int fd, struct sockaddr *addrs, int addrcnt, int flags)
{
    int setsock_option = 0;
    const char *addrbuf;
    struct sockaddr *sa_addr;
    socklen_t addrs_size = 0;
    int i;

    switch (flags)
    {
        case SCTP_BINDX_ADD_ADDR:
            setsock_option = SCTP_SOCKOPT_BINDX_ADD;
            break;
        case SCTP_BINDX_REM_ADDR:
            setsock_option = SCTP_SOCKOPT_BINDX_REM;
            break;
        default:
            errno = EINVAL;
            return -1;
    }

    addrbuf = (char*)addrs;
    for(i = 0; i < addrcnt; i++)
    {
        sa_addr = (struct sockaddr *)addrbuf;
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
        }
    }
    return setsockopt(fd, SOL_SCTP, setsock_option, addrs, addrs_size);
}
