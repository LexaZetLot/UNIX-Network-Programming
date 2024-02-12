#include "error.h"
#include "unp.h"

int daemon_proc;                                            /* устанавливается в ненулевое значение с помощью daemon_init() */

/**************************************************************/
/* Выводим сообщение и возвращаем управление. Вызывающий      */
/* процесс задает "errnoflag" и "level"                       */
/**************************************************************/
static void err_doit (int errnoflag, int level, const char *fmt, va_list ap);

void ree_ret(const char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(1, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
}

void err_sys(const char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(EXIT_FAILURE);                                            
}

void err_dump(const char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    abort();                                                 /* сохраняем дамп памяти и заканиваем работу */
    exit(EXIT_FAILURE);
}

void err_msg(const char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(0, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
}


void err_quit (const char *fmt, ...)
{
    va_list ap;
    
    va_start (ap, fmt); 
    err_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(EXIT_FAILURE);
}

static void err_doit (int errnoflag, int level, const char *fmt, va_list ap)
{
    int errno_save, n;
    char buf[MAXLINE + 1];
    
    errno_save = errno;                                      /* значение может понадобиться вызвавшему процессу */
    
#ifdef HAVE_VSNPRINTF
    vsnprintf(buf, MAXLINE, fmt, ap);                        /* защищенный вариант */
#else 
    vsprintf(buf, fmt, ap);                                  /* незащищенный вариант */
#endif
    n = strlen(buf);
    if (errnoflag)
        snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
    strcat(buf, "\n");

    if (daemon_proc)
        syslog(level, buf);
    else
    {
        fflush(stdout);                                       /* если stdout и stderr сопадают */
        fputs(buf, stderr);
        fflush(stderr);
    }
    return;
}
