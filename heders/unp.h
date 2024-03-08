/* основной заголовочный файл */ 

#ifndef __unp_h
#define __unp_h
#include "config.h"


#include <sys/types.h>                          /* основные системные типы данных */
#include <sys/socket.h>                         /* основные определения сокетов */
#include <sys/time.h>                           /* структура timeval{} для функции select() */
#include <time.h>                               /* структура timespec{} для функции pselect() */
#include <netinet/in.h>                         /* структура sockaddr_in{} и дргие сетвые оперделения */
#include <arpa/inet.h>                          /* inet(3) функции */
#include <fcntl.h>                              /* для неблокируемых сокетов */
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>                           /* для констант S_xxx */
#include <sys/uio.h>                            /* для структур iovec{} и readv/writev */
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>                             /* для доменных сокетов Unix */
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>                         /* для удобства */
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <poll.h>
#include <sys/resource.h>

#include "error.h"
#include "wrapsock.h"
#include "warpunix.h"
#include "sock_ntops.h"
#include "readn.h"
#include "writen.h"
#include "readline.h"
#include "wraplib.h"
#include "str_echo.h"
#include "wrapstdio.h"
#include "str_cli.h"
#include "signal.h"
#include "sigchldwaitpid.h"
#include "str_echo_sum.h"
#include "str_echo_bit.h"
#include "str_cli_bit.h"
#include "str_cli_select.h"
#include "dg_echo.h"
#include "dg_cli.h"
#include "dg_cliaddr.h"
#include "dg_cliconnect.h"
#include "dg_cliloop.h"
#include "dg_echoloop.h"
#include "sctp_getnostrm.h"
#include "sctp_address_to_associd.h"
#include "sctp_wrapper.h"
#include "sctpstr_cli.h"
#include "sctp_strcliecho.h"
#include "../sctp/sctp.h"
#include "host_serv.h"
#include "tcp_connect.h"
#include "sock_ntop_host.h"
#include "tcp_listen.h"
#include "udp_server.h"

#ifdef CONFIG_POLL_H
#include <poll.h>                               /* для удобства */
#endif

#ifdef HAVE_SYS_EVENT_H
#include <sys/event.h>                          /* для kqueue */
#endif

#ifdef HAVE_STRING_H
#include <string.h>                             /* для удобства */
#endif

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#ifdef HAVE_SYS_FILIO_H
#include <sys/filio.h>
#endif

#ifdef HAVE_SYS_SOCKIO_H
#include <sys/sokio.h>
#endif

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

#ifdef HAVE_NET_IF_DL_H
#include <net/if_dl.h>
#endif

/* OSF/1 фактически запрещыет recv() и send() в <sys/soket.h> */
#ifdef __osf__  
#undef recv
#undef send
#define recv(a, b, c, d) recvfrom(a, b, c, d, 0, 0)
#define send(a, b, c, d) sendto (a, b, c, d, 0, 0)
#endif

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff                  /* должно было быть в <netinet/in.h> */ 
#endif

#ifndef SHUT_RD                                 /* три новые константы POSIX.lg */
#define SHUT_RD 0                               /* отключение чтения */
#define SHUT_WR 1                               /* отключение записи */
#define SHUT_RDWR 2                             /* отключение чтения и записи */
#endif


#define INET_ADDRSTRLEN 16                      /* "ddd.ddd.ddd.ddd.\e0" */
#define INET6_ADDRSTRLEN 46                     /* xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx или xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:ddd.ddd.ddd.ddd\e0 */


#ifndef HAVE_BZERO
#define bzero(ptr, n) memset(ptr, 0, n)
#endif

#ifndef SOL_SCTP
#define SOL_SCTP 132
#endif

#ifndef SCTP_GET_PEER_ADDRS
#define SCTP_GET_PEER_ADDRS 108
#endif

#ifndef SCTP_SOCKOPT_BINDX_ADD
#define SCTP_SOCKOPT_BINDX_ADD  100
#endif


#ifndef SCTP_SOCKOPT_BINDX_REM
#define SCTP_SOCKOPT_BINDX_REM  101
#endif

#ifndef SCTP_SOCKOPT_CONNECTX_OLD
#define SCTP_SOCKOPT_CONNECTX_OLD 107
#endif

#ifndef SCTP_SOCKOPT_CONNECTX
#define SCTP_SOCKOPT_CONNECTX   110
#endif

#ifndef SCTP_SOCKOPT_CONNECTX3
#define SCTP_SOCKOPT_CONNECTX3  111
#endif

#ifndef HAVE_GETHOSTBYNAME2
#define gethostbyname2(host, family) gethostbyname((host))
#endif

/* Структура, возвращаемая функцией recvfrom_flags() */
#ifdef __UAPI_DEF_IN_PKTINFO
struct in_pktinfo
{
    struct in_addr ipi_addr;                    /* IPv4-адрес получателя */
    int ipi_ifindex;                            /* полученный индекс интерфейса */
};
#endif

#ifndef CMSG_LEN
#define CMSG_LEN(size) (sizeof(struct cmsghdr) + (size))
#endif

#ifndef CMSG_SPACE
#define CMSG_SPACE(size) (sizeof(struct cmsghdr) + (size))
#endif

#ifndef SUN_LEN
#define SUN_LEN(su) (sizeof((*su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif

#ifndef AF_LOCAL
#define AF_LOCAL AF_UNIX
#endif

#ifndef PF_LOCAL
#define PF_LOCAL PF_UNIX
#endif

#ifndef INFTIM
#define INFTIM (-1)                             /* бесконечный тайм-аут */
#ifdef HAVE_POLLPH
#define INFTIM_UNPH                             /* надо указать в unpxti.h, что эта константа определена здесь */
#endif
#endif

#define LISTENQ 1024                            /* второй аргумент функции listen() */

/* Различные константы */
#define MAXLINE 4096                            /* максимальная длина тестовой строки*/
#define BUFFSIZE 8192                           /* размер буфера для чтения и записи */

/* Определение номера порта, который может быть использован для взаимодействия клиент-сервер */
#define SERV_PORT 9877                          /* клиенты и серверы TCP и UDP */
#define SERV_PORT_STR "9877"                    /* клиенты и сервера TCP и UDP */
#define UNIXSTR_PATH "/tmp/unix.str"            /* потоковые клиенты и серверы домена Unix */
#define UNIXDG_PATH "/tmp/unix.dg"              /* клиенты и серверы протокола дейтаграмм домена Unix */
#define SERV_MAX_SCTP_STRM 10
#define SERV_MORE_STRMS_SCTP 20
#define MSG_ABORT 3

/* Дальнейшие определения сокращают преобразования типов аргументов-указателей */
#define SA struct sockaddr

#define HAVE_STRUCT_SOCKADDR_STORAGE
#ifndef HAVE_STRUCT_SOCKADDR_STORAGE
/* RFC 3493: протокольно-независимая структура адреса сокета */
#define __SS_MAXSIZE
#define __SS_ALIGNSIZE (sizeof(int64_t))
#ifndef HAVE_SOCKADDR_SA_LEN
#define __SS_PADS1SIZE (__SS_ALIGNSIZE - sizeof(u_char) - sizeof(sa_family_t))
#else
#define __SS_PAD1SIZE (__SS_ALIGNSIZE - sizeof(sa_family_t))
#endif
#define __SS_PAD@SIZE (__SS_MAXSIZE - 2*__SS_ALIGNSIZE)
struct sockaddr_storage
{
#ifdef HAVE_SOCKADDR_SA_LEN
    u_cahr ss_len;
#endif
    sa_family_t ss_family;
    cahr __ss_pad1[__SS_PAD1SIZE];
    int64_t __ss_align;
    char __ss_pad2[__SS_PAD2SIZE];
};
#endif

/* заданные по умолчанию разрешения на доступ для новых файлов */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
/* разрешения по умолчанию на доступ к файлам для новых каталогов */
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

#ifndef SIGFUNC
#define SIGFUNC
typedef void Sigfunc (int);                     /* для обработчиков сигнала */
#endif

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#ifndef HAVE_ADDRINFO_STRUCT
#include <netdb.h>
#endif

#ifndef HAVE_IF_NAMEINDEX_STRUCT
struct if_nameindex
{
    unsigned int if_index;                      /* 1, 2, ... */
    char *if_name;                              /* иям, закакнчивающееся нулем: "le)", ... */
};
#endif

#ifndef _STRUCT_TIMESPEC
struct timespec
{
    time_t tv_sec;                              /* секунд */
    long tv_nsec;                               /* и наносекунд */
};
#endif 
#endif
