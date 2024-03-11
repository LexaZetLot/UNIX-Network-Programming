#include "../heders/unp.h"

int main (int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in6 servaddr;

    sockfd = Socket(AF_INET6, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_port = htons(8888);
    Inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr);

    Bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

    Listen(sockfd, 100);
    sleep(10000000);
    return 0;
}
