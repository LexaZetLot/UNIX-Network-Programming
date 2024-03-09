#include "../heders/unp.h"

int main (int argc, char **argv)
{
    char *ptr, **pptr;
    char str[INET_ADDRSTRLEN];
    struct hostent *hptr;
    struct hostent *pp;

    while(--argc > 0)
    {
        ptr = *++argv;
        if((hptr = gethostbyname(ptr)) == NULL)
        {
            err_msg("gethostbyname error for host. %s: %s", ptr, hstrerror(h_errno));
            continue;
        }
        printf("official hostname: %s\n", hptr->h_name);

        for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
            printf("\talias: %s\n", *pptr);
        for (pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
        {

            pp = gethostbyaddr(*pptr, hptr->h_length, hptr->h_addrtype);
            printf("%s\n", pp->h_name);
        }

        switch (hptr->h_addrtype)
        {
            case AF_INET:
                pptr = hptr->h_addr_list;
                for(;*pptr != NULL; pptr++)
                    Inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
                break;
            default:
                err_ret("unknown address type");
                break;
        }
    }
    exit(0);
}
