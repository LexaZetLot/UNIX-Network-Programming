#ifndef HAVE_ERR_QUIT
#define HAVE_ERR_QUIT
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void err_quit(const char *fml, ...);
void err_sys(const char* str);

#endif 
