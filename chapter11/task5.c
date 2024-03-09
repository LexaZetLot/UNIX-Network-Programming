#include "../heders/unp.h"
#include <netinet/in.h>

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    struct sockaddr_in6 servaddr6;
    struct sockaddr *sa;
    socklen_t size;
    struct in_addr **pptr, *addrs[2];
    struct hostent *hp;
    struct servent *sp;

    if(argc != 3)
        err_quit("usage: daytimetcpcli2 <hostname> <service>");
    if((hp = gethostbyname(argv[1])) != NULL)
        err_quit("gethostbyname error for %s", argv[1]);
    if((sp = getservbyname(argv[2], "tcp")) != NULL)
        err_quit("getservbyname error for %s", argv[2]);

    pptr = (struct in_addr **) hp->h_addr_list;
    for(; *pptr != NULL; pptr++)
    {
        sockfd = Socket(hp->h_addrtype, SOCK_STREAM, 0);

        if(hp->h_addrtype == AF_INET)
        {
            sa = (SA *) &servaddr;
            size = sizeof(servaddr);
        }
        else if(hp->h_addrtype == AF_INET6)
        {
            sa = (SA *) &servaddr6;
            size = sizeof(servaddr6);
        }
        else
            err_quit("error");
        bzero(sa, size);
        sa->sa_family = hp->h_addrtype;
        sock_set_port(sa, size, sp->s_port);
        sock_set_addr(sa, size, *pptr);

        printf("trying %s\n", Sock_ntop(sa, size));

        if (connect(sockfd, sa, size) == 0)
            break;
        err_ret("connect error");
        Close(sockfd);
    }
    if(*pptr == NULL)
        err_quit("unable to connect");

    while((n = Read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }
    exit(0);
}
