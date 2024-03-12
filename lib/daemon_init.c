#include "../heders/unp.h"
#include <syslog.h>

#define MAXFD 64

extern int daemon_proc;             /* определен в error.c */

int daemon_init(const char *pname, int facility)
{
    int i;
    pid_t pid;

    if((pid = Fork()) < 0)
        return (-1);
    else if (pid)
        _exit(0);                   /* родитель завершается */

    /* 1-й дочерний процесс продолжает работу... */

    if(setsid() < 0)                /* становится главным процессом сеанса */
        return (-1);

    Signal(SIGHUP, SIG_IGN);
    if((pid = Fork()) < 0)
        return (-1);
    else if (pid)
        _exit(0);                   /* 1-й дочерний процесс завершается */

    /* 2-й дочерний процесс продолжает работу */

    daemon_proc = 1;                /* для функции err__XXX() */

    chdir("/");                     /* смена текущего каталога */

    /* закрытие дескрипторов файлов */
    for(i = 0; i < MAXFD; i++)
        close(i);

    /* перенаправление stdin, stdout и stderr в /dev/null */
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    openlog(pname, LOG_PID, facility);

    return (0);                     /* успешное завершение */
}
