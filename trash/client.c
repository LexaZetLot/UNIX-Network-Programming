#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv)
{
    int sockfd;
    char ch[] = " ";
    char buf[1024];
    struct sockaddr_in servaddr;

    /*if(argc != 2)
    {
        printf("usage: tcpcli <IPaddress>");
        exit(0);
    }*/

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(strtol(argv[2], NULL, 10));
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        printf("connect error");

    strcpy(buf, argv[1]);
    strcpy(buf + strlen(argv[1]), ch);
    strcpy(buf + strlen(argv[1]) + strlen(ch), argv[3]);
    printf("%s", buf);

    write(sockfd, buf, sizeof(argv[1]) + sizeof(argv[3]));

    exit(0);
}
