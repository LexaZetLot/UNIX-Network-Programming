#include "../heders/unp.h"

int main (int argc, char **argv)
{
    int fd;
    int rcvbuf;
    socklen_t len = 4;

    fd = Socket(AF_INET, SOCK_STREAM, 0);
    getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);
    printf("TCP SO_RCVBUF: %d\n", rcvbuf);
    getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &rcvbuf, &len);
    printf("TCP SO_SNDBUF: %d\n", rcvbuf);

    fd = Socket(AF_INET, SOCK_DGRAM, 0);
    getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);
    printf("UDP SO_RCVBUF: %d\n", rcvbuf);
    getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &rcvbuf, &len);
    printf("UDP SO_SNDBUF: %d\n", rcvbuf);

    fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
    getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);
    printf("SMTP SO_RCVBUF: %d\n", rcvbuf);
    getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &rcvbuf, &len);
    printf("SMTP SO_SNDBUF: %d\n", rcvbuf);

    return 0;
}
