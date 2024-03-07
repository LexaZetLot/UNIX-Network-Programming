#include "../heders/unp.h"

struct addrinfo *host_serv(const char *host, const char *serv, int family, int socktype)
{
    int n;
    struct addrinfo hints, *res;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_CANONNAME;          /* всегда возвращает каноническое имя */
    hints.ai_family = family;               /* AF_UNSPEC, AF_INET, AF_INET6, ...  */
    hints.ai_socktype = socktype;           /* 0, SOCK_STREAM, SOCK_DGRAM, ...    */

    if((n = getaddrinfo(host, serv, &hints, &res)) != 0)
        return NULL;

    return res;                             /* возвращает указатель на первый     */
}                                           /* элемент в связном списке           */
