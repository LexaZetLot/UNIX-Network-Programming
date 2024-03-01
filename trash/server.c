#include <sys/socket.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    FILE *fp = fopen("log.txt", "a+w");
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    ssize_t n;
    char buf[1024];
    time_t timer;
    char bufer[26];
    int millisec;
    struct timeval tv;
    struct tm* tm_info;
    int num;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(3000);

    if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        printf("bind error");
    listen(listenfd, 1024);

    for (;;)
    {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

        if((childpid = fork()) == 0)
        {
            if(close(listenfd) == -1){}

            if(read(connfd, buf, 10) > 0)
            {
                gettimeofday(&tv, NULL);
                millisec = lrint(tv.tv_usec/1000.0);
                if (millisec>=1000)
                {
                    millisec -=1000;
                    tv.tv_sec++;
                }
                tm_info = localtime(&tv.tv_sec);
                strftime(bufer, 25, "%Y-%m-%d %H:%M:%S", tm_info);
                for (int i = 0; i < strlen(buf); i++)
                    if(isspace(buf[i]))
                    {
                        num = atoi(buf + i + 1);
                        buf[i] = '\0';
                        break;
                    }
                fprintf(fp, "[%s.%03d] %s\n", bufer, millisec, buf);

                sleep(num);
                gettimeofday(&tv, NULL);
                millisec = lrint(tv.tv_usec/1000.0);
                if (millisec>=1000)
                {
                    millisec -=1000;
                    tv.tv_sec++;
                }
                tm_info = localtime(&tv.tv_sec);
                strftime(bufer, 25, "%Y-%m-%d %H:%M:%S", tm_info);
                fprintf(fp, "[%s.%03d] %s\n", bufer, millisec, buf);
            }
            exit(0);
        }
        if(close(listenfd) == -1){}
    }
}

