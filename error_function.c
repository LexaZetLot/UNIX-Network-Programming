#include "error_function.h"
#include <stdlib.h>

void err_quit (const char *fmt, ...)
{
    va_list args;
    
    va_start (args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

void err_sys (const char* str)
{
    perror (str);
    exit(EXIT_FAILURE);
}
