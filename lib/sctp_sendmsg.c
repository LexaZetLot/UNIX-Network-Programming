#include "../heders/unp.h"

ssize_t sctp_sendmsg(int s, const void *msg, size_t len, struct sockaddr *to, socklen_t tolen, uint32_t ppid, uint32_t flags, uint16_t stream_no, uint32_t timetolive, uint32_t context)
{
    ssize_t num;
    struct msghdr outmsg;
    struct iovec iov;
    char outcmsg[CMSG_SPACE(sizeof(struct sctp_sndrcvinfo))];
    struct cmsghdr *cmsg;
    struct sctp_sndrcvinfo *sinfo;

    outmsg.msg_name = to;
    outmsg.msg_namelen = tolen;
    outmsg.msg_iov = &iov;
    iov.iov_base = (void *)msg;
    iov.iov_len = len;
    outmsg.msg_iovlen = 1;

    outmsg.msg_control = outcmsg;
    outmsg.msg_controllen = sizeof(outcmsg);
    outmsg.msg_flags = 0;

    cmsg = CMSG_FIRSTHDR(&outmsg);
    cmsg->cmsg_level = IPPROTO_SCTP;
    cmsg->cmsg_type = SCTP_SNDRCV;
    cmsg->cmsg_len = CMSG_LEN(sizeof(struct sctp_sndrcvinfo));

    outmsg.msg_controllen = cmsg->cmsg_len;
    sinfo = (struct sctp_sndrcvinfo *)CMSG_DATA(cmsg);
    memset(sinfo, 0, sizeof(struct sctp_sndrcvinfo));
    sinfo->sinfo_ppid = ppid;
    sinfo->sinfo_flags = flags;
    sinfo->sinfo_stream = stream_no;
    sinfo->sinfo_timetolive = timetolive;
    sinfo->sinfo_context = context;

    num = sendmsg(s, &outmsg, 0);
    return num;
}


ssize_t sctp_send(int s, const void *msg, size_t len, const struct sctp_sndrcvinfo *sinfo, int flags)
{
    struct msghdr outmsg = {};
    struct iovec iov;
    char outcmsg[CMSG_SPACE(sizeof(struct sctp_sndrcvinfo))];

    outmsg.msg_iov = &iov;
    iov.iov_base = (void *)msg;
    iov.iov_len = len;
    outmsg.msg_iovlen = 1;
    outmsg.msg_flags = flags;

    if (sinfo)
    {
        struct cmsghdr *cmsg;

        outmsg.msg_control = outcmsg;
        outmsg.msg_controllen = sizeof(outcmsg);

        cmsg = CMSG_FIRSTHDR(&outmsg);
        cmsg->cmsg_level = IPPROTO_SCTP;
        cmsg->cmsg_type = SCTP_SNDRCV;
        cmsg->cmsg_len = CMSG_LEN(sizeof(struct sctp_sndrcvinfo));

        outmsg.msg_controllen = cmsg->cmsg_len;
        memcpy(CMSG_DATA(cmsg), sinfo, sizeof(struct sctp_sndrcvinfo));
    }
    return sendmsg(s, &outmsg, flags);
}

#ifdef HAVE_SCTP_SENDV
static struct cmsghdr *sctp_sendv_store_cmsg(struct cmsghdr *cmsg, int *cmsglen, int type, int len, void *data)
{
    cmsg->cmsg_level = IPPROTO_SCTP;
    cmsg->cmsg_type = type;
    cmsg->cmsg_len = CMSG_LEN(len);
    memcpy(CMSG_DATA(cmsg), data, len);

    *cmsglen += CMSG_SPACE(len);

    return (struct cmsghdr *)((char *)cmsg + CMSG_SPACE(len));
}

int sctp_sendv(int s, const struct iovec *iov, int iovcnt, struct sockaddr *addrs, int addrcnt, void *info, socklen_t infolen, unsigned int infotype, int flags)
{
    char _cmsg[CMSG_SPACE(sizeof(struct sctp_sndinfo)) + CMSG_SPACE(sizeof(struct sctp_prinfo)) + CMSG_SPACE(sizeof(struct sctp_authinfo))];
    struct cmsghdr *cmsg = (struct cmsghdr *)_cmsg;
    struct msghdr outmsg = {};
    struct sockaddr *addr;
    int len, cmsglen = 0;
    int err, type, i;
    char *addrbuf;

    outmsg.msg_iov = (struct iovec *)iov;
    outmsg.msg_iovlen = iovcnt;
    outmsg.msg_flags = flags;


    if (addrs && addrcnt)
    {
        outmsg.msg_name = addrs;
        if (addrs->sa_family == AF_INET)
            outmsg.msg_namelen = sizeof(struct sockaddr_in);
        else if (addrs->sa_family == AF_INET6)
            outmsg.msg_namelen = sizeof(struct sockaddr_in6);
        else
            return -EINVAL;
        addrcnt -= 1;
        addrbuf = (char *)addrs;
        addrs = (struct sockaddr *)(addrbuf + outmsg.msg_namelen);
    }

    if (addrcnt)
    {
        len = CMSG_SPACE(sizeof(struct sockaddr_in6)) * addrcnt;
        cmsg = malloc(sizeof(_cmsg) + len);
        if (!cmsg)
            return -ENOMEM;
    }

    outmsg.msg_control = cmsg;

    for (i = 0, addrbuf = (char *)addrs; i < addrcnt; i++)
    {
        void *ainfo;

        addr = (struct sockaddr *)addrbuf;
        if (addr->sa_family == AF_INET)
        {
            struct sockaddr_in *a = (struct sockaddr_in *)addrbuf;

            len = sizeof(struct in_addr);
            type = SCTP_DSTADDRV4;
            ainfo = &a->sin_addr;
            addrbuf += sizeof(*a);
        }
        else if (addr->sa_family == AF_INET6)
        {
            struct sockaddr_in6 *a = (struct sockaddr_in6 *)addrbuf;
            len = sizeof(struct in6_addr);
            type = SCTP_DSTADDRV6;
            ainfo = &a->sin6_addr;
            addrbuf += sizeof(*a);
        }
        else
        {
            free(outmsg.msg_control);
            return -EINVAL;
        }

        cmsg = sctp_sendv_store_cmsg(cmsg, &cmsglen, type, len, ainfo);
    }
    if (infotype == SCTP_SENDV_SPA)
    {
        struct sctp_sendv_spa *spa = info;

        if (spa->sendv_flags & SCTP_SEND_SNDINFO_VALID)
        {
            type = SCTP_SNDINFO;
            len = sizeof(struct sctp_sndinfo);
            cmsg = sctp_sendv_store_cmsg(cmsg, &cmsglen, type, len, &spa->sendv_sndinfo);
        }
        if (spa->sendv_flags & SCTP_SEND_PRINFO_VALID)
        {
            type = SCTP_PRINFO;
            len = sizeof(struct sctp_prinfo);
            cmsg = sctp_sendv_store_cmsg(cmsg, &cmsglen, type, len, &spa->sendv_prinfo);
        }
        if (spa->sendv_flags & SCTP_SEND_AUTHINFO_VALID)
        {
            type = SCTP_AUTHINFO;
            len = sizeof(struct sctp_authinfo);
            sctp_sendv_store_cmsg(cmsg, &cmsglen, type, len, &spa->sendv_authinfo);
        }
    }
    else if (infotype == SCTP_SENDV_SNDINFO)
    {
        type = SCTP_SNDINFO;
        len = sizeof(struct sctp_sndinfo);
        sctp_sendv_store_cmsg(cmsg, &cmsglen, type, len, info);
    }
    else if (infotype == SCTP_SENDV_PRINFO)
    {
        type = SCTP_PRINFO;
        len = sizeof(struct sctp_prinfo);
        sctp_sendv_store_cmsg(cmsg, &cmsglen, type, len, info);
    }
    else if (infotype == SCTP_SENDV_AUTHINFO)
    {
        type = SCTP_AUTHINFO;
        len = sizeof(struct sctp_authinfo);
        sctp_sendv_store_cmsg(cmsg, &cmsglen, type, len, info);
    }

    outmsg.msg_controllen = cmsglen;
    err = sendmsg(s, &outmsg, 0);
    if (outmsg.msg_control != _cmsg)
        free(outmsg.msg_control);

    return err;
}
#endif
