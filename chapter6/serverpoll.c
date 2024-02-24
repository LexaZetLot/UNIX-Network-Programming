#include "../heders/unp.h"
#include <limits.h>                                         /* для OPEN_MAX */

int main(int argc, char **argv)
{
   int i, maxi, listenfd, connfd, sockfd;
   int nready;
   ssize_t n;
   char buf[MAXLINE];
   socklen_t clilen;
   struct pollfd client[FOPEN_MAX];
   struct sockaddr_in cliaddr, servaddr;

   listenfd = Socket(AF_INET, SOCK_STREAM, 0);

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(SERV_PORT);

   Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

   Listen(listenfd, LISTENQ);

   client[0].fd = listenfd;
   client[0].events = POLLRDBAND;
   for(i = 1; i < FOPEN_MAX; i++)
       client[i].fd = -1;                                   /* -1 означает, что элемент свободен */
    maxi = 0;                                               /* максимальный индекс массива client[] */

    for(;;)
    {
        nready = Poll(client, maxi + 1, INFTIM);

        if(client[0].revents & POLLRDNORM)                  /* новое соединение с клиентом */
        {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

            for(i = 1; i < FOPEN_MAX; i++)
                if(client[i].fd < 0)
                {
                    client[i].fd = connfd;                  /* сохраняем дескриптор */
                    break;
                }
            if(i == FOPEN_MAX)
                err_quit("too many clients");

            client[i].events = POLLRDNORM;
            if(i > maxi)
                maxi = i;                                   /* максимальный индекс в массиве client[] */

            if(--nready <= 0)
                continue;                                   /* больше нет дескрипторов, готовых для чтения */
        }
        for(i = 1; i <= maxi; i++)                          /* проверяем все клиенты на наличие данных */
        {
            if((sockfd = client[i].fd) < 0)
                continue;
            if(client[i].revents & (POLLRDNORM | POLLERR))
            {
                if((n = Read(sockfd, buf, MAXLINE)) < 0)
                {
                    if(errno == ECONNRESET)                 /* соединение переустановлено клиентом */
                    {
                        Close(sockfd);
                        client[i].fd = -1;
                    }
                    else
                        err_sys("readline error");
                }
                else if(n == 0)                             /* соединение закрыто клиентом */
                {
                    Close(sockfd);
                    client[i].fd = -1;
                }
                else
                    Writen(sockfd, buf, n);

                if(--nready <= 0)
                    break;                                  /* больше нет дескрипторов, готовых для чтения */
            }
        }
    }
}
