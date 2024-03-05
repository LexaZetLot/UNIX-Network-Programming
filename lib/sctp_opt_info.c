#include "../heders/unp.h"

int sctp_opt_info(int sd, sctp_assoc_t id, int opt, void *arg, socklen_t *size)
{
    switch(opt)
    {
        case SCTP_RTOINFO:
        case SCTP_ASSOCINFO:
        case SCTP_INITMSG:
        case SCTP_NODELAY:
        case SCTP_AUTOCLOSE:
        case SCTP_PRIMARY_ADDR:
        case SCTP_DISABLE_FRAGMENTS:
        case SCTP_PEER_ADDR_PARAMS:
        case SCTP_DEFAULT_SEND_PARAM:
        case SCTP_EVENT:
        case SCTP_I_WANT_MAPPED_V4_ADDR:
        case SCTP_MAXSEG:
        case SCTP_STATUS:
        case SCTP_GET_PEER_ADDR_INFO:
        case SCTP_AUTH_ACTIVE_KEY:
        case SCTP_PEER_AUTH_CHUNKS:
        case SCTP_LOCAL_AUTH_CHUNKS:
            *(sctp_assoc_t *)arg = id;
            return getsockopt(sd, IPPROTO_SCTP, opt, arg, size);
        default:
            return ENOTSUP;
    }
}
