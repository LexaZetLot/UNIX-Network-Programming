#include "../heders/unp.h"

int main (int argc, char **argv)
{
    union{
        short s;
        char c[sizeof(short)];
    }un;

    un.s = 0x0102;
    if(sizeof(short) == 2)
    {
        if(un.c[0] == 1 && un.c[1] == 2)
            printf("big-endian\n");
        else if (un.c[0] == 2 && un.c[1] == 1)
            printf("littel-endian\n");
        else
            printf("uknown\n");
    }
    else
        printf("sizeof(short) = %lu\n", sizeof(short));
    exit(0);
}
