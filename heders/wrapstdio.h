#ifndef WRAPSTDIO_H
#define WRAPSTDIO_H
#include <stdio.h>

void Fclose(FILE *fp);
FILE *Fdopen(int fd, const char *type);
char *Fgets(char *ptr, int n, FILE *stream);
FILE *Fopen(const char *filename, const char *mode);
void Fputs(const char *ptr, FILE *stream);

#endif
