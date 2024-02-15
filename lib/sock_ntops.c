#include "../heders/unp.h"

char *sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
    char portstr[8];
    static char str[128];

    switch (sa->sa_family)
    {
    case AF_INET:
    {
        struct sockaddr_in *sin = (struct sockaddr_in *) sa;

        if(inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
            return NULL;
        if(ntohs(sin->sin_port) != 0)
        {
            snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
            strcat(str, portstr);
        }
        return str;
    }
    case AF_INET6:
    {
        struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) sa;
        str[0] = '[';
        if (inet_ntop(AF_INET6, &sin6->sin6_addr, str + 1, sizeof(str) - 1) == NULL)
            return NULL;
        if (ntohs(sin6->sin6_port) != 0)
        {
            snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin6->sin6_port));
            strcat(str, portstr);
            return str;
        }
    }
    case AF_UNIX:
    {
        struct sockaddr_un *unp = (struct sockaddr_un *) sa;

        if(unp->sun_path[0] == 0)
            strcpy(str, "(no pathname bound)");
        else
            snprintf(str, sizeof(str), "%s", unp->sun_path);
        return str;
    }
    /*
    case AF_NETLINK:
    {
        struct sockaddr_dl *sdl = (struct sockaddr_dl *) sa;

        if(sdl->sdl_nlen > 0)
            snprintf(str, sizeof(str), "%*s (index %d)", sdl->sdl_nlen, &sdl->sdl_data[0], sdl-sdl_index);
        else
            snprintf(str, sizeof(str), "AF_LINK, index=%d", sdl->sdl_index);

        return str;
    }
    */
    default:
        snprintf(str, sizeof(str), "sock_ntop: unknow AF_xxx: %d, len %d", sa->sa_family, salen);
        return(str);
    }
    return NULL;
}

char *Sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
    char *ptr;

    if((ptr = sock_ntop(sa, salen)) == NULL)
        err_sys("sock_not error");

    return ptr;
}
