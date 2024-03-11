#include "../heders/unp.h"

int main (int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

    Listen(sockfd, 100);
    sleep(10000000);
    return 0;
}
