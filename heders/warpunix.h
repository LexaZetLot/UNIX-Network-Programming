#ifndef WARPUNIX_H
#define WARPUNIX_H
#include <stdlib.h>

void *Calloc(size_t n, size_t size);
void Close(int fd);
void Dup2(int fd1, int fd2);
int Fcntl(int fd, int cmd, int arg);
void Gettimeofday(struct timeval * tv, void *foo);
int Ioctl(int fd, int request, void *arg);
pid_t Fork(void);
void * Malloc(size_t size);
int Mkstemp(char *templat);
void * Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
int Open(const char *pathname, int oflag, mode_t mode);
void Pipe(int *fds);
ssize_t Read(int fd, void *ptr, size_t nbytes);
void Sigaddset(sigset_t *set,int signo);
void Sigdelset(sigset_t *set, int signo);
void Sigfillset(sigset_t *set);
int Sigismember(const sigset_t *set, int signo);
void Sigpending(sigset_t *set);
void Sigprocmask(int how, const sigset_t *set, sigset_t *oset);
char *Strdup(const char *str);
long Sysconf(int name);
#ifdef CONFIG_SYSCTL_H
void Sysctl(int *name, u_int namelen, void *oldp, size_t *oldlenp, void *newp, size_t newlen);
#endif
void Unlink(const char *pathname);
pid_t Wait(int *iptr);
pid_t Waitpid(pid_t pid, int *iptr, int options);
void Write(int fd, void *ptr, size_t nbytes);

#endif
