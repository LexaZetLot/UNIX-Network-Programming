#include "../heders/unp.h"
#include <arpa/inet.h>

int inet_pton_loose(int af, const char *restrict src, void *restrict dst);

int main (int argc, char **argv)
{

    struct sockaddr_in6 stu;

    printf ("%d\n", inet_pton_loose(AF_INET6, "127.0.0.1", &stu));
    for(int i = 0; i < 16; i++)
        printf("%d", stu.sin6_addr.s6_addr[i]);
    printf("\n");
    exit (0);
}

int inet_pton_loose(int af, const char *restrict src, void *restrict dst)
{
    if((af == AF_INET && inet_pton(af, src, dst) == 0) || (af == AF_INET6 && inet_pton(af, src, dst) == 0))
        return 1;
    else
        return inet_aton(src, &((struct sockaddr_in *)dst)->sin_addr);
}
