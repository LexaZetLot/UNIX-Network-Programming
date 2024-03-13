#include "../heders/unp.h"
#include <sys/poll.h>

void str_cli_poll(FILE *fp, int sockfd)
{
    int stdineof;
    char buf[MAXLINE];
    int  n;
    int  wfd;
    struct pollfd pollfd[2];
    struct dvpoll dopoll;
    int i;
    int result;

    wfd = Open("/dev/poll", O_RDWR, 0);

    pollfd[0].fd = fileno(fp);
    pollfd[0].events = POLLIN;
    pollfd[0].revents = 0;

    pollfd[1].fd = sockfd;
    pollfd[1].events = POLLIN;
    pollfd[1].revents = 0;

    Write(wfd, pollfd, sizeof(struct pollfd) * 2);

    stdineof = 0;
    for(;;)
    {
        /* блокирование до готовности сокета */
        dopoll.dp_timeout = -1;
        dopoll.dp_nfds = 2;
        dopoll.dp_fds = pollfd;
        result = Ioctl(wfd, DP_POLL, &dopoll);

        /* цикл по готовым дескрипторам */
        for(i = 0; i < result; i++)
        {
            if(dopoll.dp_fds[i].fd == sockfd)
            {
                /* сокет готов к чтению */
                if((n = Read(sockfd, buf, MAXLINE)) == 0)
                {
                    if(stdineof == 1)
                        return;             /* нормальное завершение */
                    else
                        err_quit("str_cli: server terminated prematurely");
                }

            Write(fileno(stdout), buf, n);
            }
            else
            {
                /* дескриптор готов к чтению */
                if((n = Read(fileno(fp), buf, MAXLINE)) == 0)
                {
                    stdineof = 1;
                    Shutdown(sockfd, SHUT_WR);      /* отправка FIN */
                    continue;
                }
                Writen(sockfd, buf, n);
            }
        }
    }
}
