#include "../heders/unp.h"

int main(int argc, char **argv)
{
    int i, maxi, maxfd, listenfd, connfd, sockfd;
    int nready, client[FD_SETSIZE];
    ssize_t n;
    fd_set rset, allset;
    char buf[MAXLINE];
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    maxfd = listenfd;                               /* инициализация */
    maxi = -1;                                      /* индекс в массиве client[] */
    for(int i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;                             /* -1 означает свободный элемент */
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for (;;)
    {
        rset = allset;                              /* присваивание значений структуре */
        nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, &rset))               /* соединение с новым клиентом */
        {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

            for(i = 0; i < FD_SETSIZE; i++)
                if(client[i] < 0)
                {
                    client[i] = connfd;             /* сохраняем дескриптор */
                    break;
                }
            if(i == FD_SETSIZE)
                err_quit("too many clients");

            FD_SET(connfd, &allset);                /* добавление нового дескриптора */
            if(connfd > maxfd)
                maxfd = connfd;                     /* для функции select */
            if(i > maxi)
                maxi = i;                           /* максимальный индекс в массиве client[] */

            if(--nready <= 0)
                continue;                           /* больше нет дескрипторовб готовых для чтения */
        }
        for(i = 0; i <= maxi; i++)                  /* проверяем все клиенты на наличие данных */
        {
            if((sockfd = client[i]) < 0)
                continue;
            if(FD_ISSET(sockfd, &rset))
            {
                if((n = Read(sockfd, buf, MAXLINE)) == 0)/* соединение закрыто клиентом */
                {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else
                    Writen(sockfd, buf, n);

                if(--nready <= 0)
                    break;                          /* больше нет дескрипторов, готовых для чтения */
            }
        }
    }
}
