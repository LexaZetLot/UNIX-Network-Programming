#include "../heders/unp.h"

int main (int argc, char **argv)
{
    int sockfd, n;
    struct sockaddr_in servaddr;
    struct hostent *hp;
    struct servent *sp;

    if(argc != 3)
        err_quit("uage: udpcli <IPaddress>");
     if((hp = gethostbyname(argv[1])) != NULL)
        err_quit("gethostbyname error for %s", argv[1]);
    if((sp = getservbyname(argv[2], "udp")) != NULL)
        err_quit("getservbyname error for %s", argv[2]);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = hp->h_addrtype;
    servaddr.sin_port = htons(sp->s_port);
    Inet_pton(AF_INET, hp->h_addr_list[0], &servaddr.sin_addr);

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

    exit(0);
}
