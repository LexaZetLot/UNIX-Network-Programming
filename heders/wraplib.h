#ifndef WRAPLIB_H
#define WRAPLIB_H
#include <stdlib.h>

const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
void Inet_pton(int family, const char *strptr, void *addrptr);

#endif
