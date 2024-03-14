#include "../heders/unp.h"
#include <unistd.h>

void sig_chld(int signo);

int main (int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_un cliaddr, servaddr;

    listenfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

    unlink(UNIXSTR_PATH);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);

    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);
    Signal(SIGCHLD, sig_chld);

    for(;;)
    {
        clilen = sizeof(cliaddr);
        if((connfd = accept(listenfd, (SA *)&cliaddr, &clilen)) < 0)
        {
            if(errno == EINTR)
                continue;                   /* назад в for() */
            else
                err_sys("accept error");
        }
        if((childpid = Fork()) == 0)        /* дочерний процесс */
        {
            Close(listenfd);                /* закрывается прослушиваемый сокет */
            str_echo(connfd);               /* обработка запроса */
            exit(0);
        }
        Close(connfd);
    }
    exit(0);
}

void sig_chld(int signo)
{
    return;
}
