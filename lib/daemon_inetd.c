#include "../heders/unp.h"
#include <syslog.h>

extern int daemon_proc;         /* определено в error.c */

void daemon_inetd(const char *pname, int facility)
{
    daemon_proc = 1;            /* для наших функций err_XXX() */
    openlog(pname, LOG_PID, facility);
}
