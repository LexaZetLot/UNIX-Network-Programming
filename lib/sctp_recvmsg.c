#include "../heders/unp.h"

ssize_t sctp_recvmsg(int s, void *msg, size_t len, struct sockaddr *from, socklen_t *fromlen, struct sctp_sndrcvinfo *sinfo, int *msg_flags)
{
    ssize_t error;
    struct iovec iov;
    struct msghdr inmsg;
    char incmsg[CMSG_SPACE(sizeof(struct sctp_sndrcvinfo))];
    struct cmsghdr *cmsg = NULL;

    memset(&inmsg, 0, sizeof (inmsg));

    iov.iov_base = msg;
    iov.iov_len = len;

    inmsg.msg_name = from;
    inmsg.msg_namelen = fromlen ? *fromlen : 0;
    inmsg.msg_iov = &iov;
    inmsg.msg_iovlen = 1;
    inmsg.msg_control = incmsg;
    inmsg.msg_controllen = sizeof(incmsg);

    error = recvmsg(s, &inmsg, msg_flags ? *msg_flags : 0);
    printf("%lu\n", error);
    if (error < 0)
        return error;

    if (fromlen)
        *fromlen = inmsg.msg_namelen;
    if (msg_flags)
        *msg_flags = inmsg.msg_flags;

    if (!sinfo)
        return error;

    for (cmsg = CMSG_FIRSTHDR(&inmsg); cmsg != NULL; cmsg = CMSG_NXTHDR(&inmsg, cmsg))
        if ((IPPROTO_SCTP == cmsg->cmsg_level) && (SCTP_SNDRCV == cmsg->cmsg_type))
            break;

    if (cmsg)
        memcpy(sinfo, CMSG_DATA(cmsg), sizeof(struct sctp_sndrcvinfo));

    return (error);
}

#ifdef HAVE_SCTP_SENDV
int sctp_recvv(int s, const struct iovec *iov, int iovlen, struct sockaddr *from, socklen_t *fromlen, void *info, socklen_t *infolen, unsigned int *infotype, int *flags)
{
    char incmsg[CMSG_SPACE(sizeof(struct sctp_rcvinfo)) + CMSG_SPACE(sizeof(struct sctp_nxtinfo))];
    int error, len, _infolen;
    struct cmsghdr *cmsg;
    struct msghdr inmsg;

    memset(&inmsg, 0, sizeof(inmsg));

    inmsg.msg_name = from;
    inmsg.msg_namelen = fromlen ? *fromlen : 0;
    inmsg.msg_iov = (struct iovec *)iov;
    inmsg.msg_iovlen = iovlen;
    inmsg.msg_control = incmsg;
    inmsg.msg_controllen = sizeof(incmsg);

    error = recvmsg(s, &inmsg, flags ? *flags : 0);
    if (error < 0)
        return error;

    if (fromlen)
        *fromlen = inmsg.msg_namelen;

    if (flags)
        *flags = inmsg.msg_flags;

    if (!info || !infotype || !infolen)
        return error;

    *infotype = SCTP_RECVV_NOINFO;
    _infolen = *infolen;

    for (cmsg = CMSG_FIRSTHDR(&inmsg); cmsg != NULL; cmsg = CMSG_NXTHDR(&inmsg, cmsg))
    {
        if (cmsg->cmsg_level != IPPROTO_SCTP)
            continue;

        if (cmsg->cmsg_type == SCTP_RCVINFO)
        {
            len = sizeof(struct sctp_rcvinfo);
            if (*infotype == SCTP_RECVV_NOINFO)
            {
                if (_infolen < len)
                    break;
                memcpy(info, CMSG_DATA(cmsg), len);
                *infotype = SCTP_RECVV_RCVINFO;
                *infolen = len;
            }
            else if (*infotype == SCTP_RECVV_NXTINFO)
            {
                if (_infolen < len + sizeof(struct sctp_nxtinfo))
                    break;
                memcpy(info + len, info, sizeof(struct sctp_nxtinfo));
                memcpy(info, CMSG_DATA(cmsg), len);
                *infotype = SCTP_RECVV_RN;
                *infolen = len + sizeof(struct sctp_nxtinfo);
            }
            else
                break;
        }
        else if (cmsg->cmsg_type == SCTP_NXTINFO)
        {
            len = sizeof(struct sctp_nxtinfo);
            if (*infotype == SCTP_RECVV_NOINFO)
            {
                if (_infolen < len)
                    break;
                memcpy(info, CMSG_DATA(cmsg), len);
                *infotype = SCTP_RECVV_NXTINFO;
                *infolen = len;
            }
            else if (*infotype == SCTP_RECVV_RCVINFO)
            {
                if (_infolen < len + sizeof(struct sctp_rcvinfo))
                    break;
                memcpy(info + sizeof(struct sctp_rcvinfo), CMSG_DATA(cmsg), len);
                *infotype = SCTP_RECVV_RN;
                *infolen = len + sizeof(struct sctp_rcvinfo);
            }
            else
                break;
        }
    }
    return error;
}
#endif
