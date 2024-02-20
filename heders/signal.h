#ifndef SIGNAL_H
#define SIGNAL_H
#ifndef SIGFUNC
typedef void Sigfunc (int);
#endif

Sigfunc *Signal(int signo, Sigfunc *func);

#endif
