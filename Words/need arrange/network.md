# net
一、什么是socket？可以看成是用户进程与内核网络协议栈的编程接口。
socket不仅可以用于本机的进程间的通信，还可以用于网络上不同主机的进程间通信。
它与PIPE管道不同在于，管道只能在本机进程间通信，而socket能用于异构系统间通信。
知识点1.IPv4套接字结构：
struct sockaddr_in{
    uint8_t    sin_len;                //整个socketaddr_in结构体的长度
    sa_family_t    sin_family;    //指定该地址家族。用来标定使用什么协议
    in_port_t    sin_port;            //16位无符号整数，2字节
    struct    in_addr    sin_addr;//IPv4地址，该地址是32位的
    char sin_zero[8];            //
}
可以使用man 7 ip来查看
需要：#include <netinet/ip.h>

通用地址结构。为什么还会有通用地址结构呢?一般是使用socket_in结构体进行填充，最终强制转换为通用的socketaddr地址结构。

知识点2.网络字节序
为什么要引入字节序这个概念呢？
因为Socket可以用于异构系统之间的通讯，不同的硬件平台，对于一个整数，存放形式是不一样的，有的机器采用的是大端字节序，有的是使用小端字节序，这时传输给其他机器的编码可能会出错，字节序不一样，得到的值就会错误。这时候就需要统一一下字节序，这个就叫做网络字节序。网络字节序规定为  大端字节序。

字节序分为大端字节序和小端字节序。
大端字节序（Big Endian）
最高有效位（MSB）存储于最低内存地址处，最低有效位（LSB）存储于最高内存地址处。

小端字节序：
最高有效位（MSB）存储于最高内存地址处，最低有效位（LSB）存储于最低内存地址处。

字节序的转换函数：
uint32_t    htonl(uint32_t    hostlong);
uint16_t    htons(uint16_t    hostshort);
uint32_t    htohl(uint32_t    netlong);
uint16_t    htohs(uint16_t    netshort);

h代表host；n代表network；s代表short；l代表long

知识点3.地址转换函数
//把平常我们看到的ip地址的.形式转换成32位整型
in_addr_t inet_addr(const char *cp);
//将32位的整数转换为.的形式
char    *inet_ntoa(struct in_addr in);

知识点4.套接字类型：
流式套接字（SOCK_STREAM）提供面向连接的、可靠的数据传输服务，数据无差错，无重复的发送，且按发送顺序接收。
数据报式套接字（SOCK_DGRAM）
提供无连接服务。不提供无错保证，数据可能丢失或重复，并且接收顺序混乱。
原始套接字（SOCK_RAW）
它提供了一种能力，让我们跨越了传输层，直接对ip层进行数据封装的套接字，通过原始套接字，直接通过应用层进行封装成ip层能够识别的的协议格式。



二  三、socket小例子
source:
client.c    serve,c    echosrv.c    echocli.c    p2psrv.c    p2pcli.c
ctrl+z和ctrl+c的区别：
ctrl+c：强制中断程序的执行，进程已经终止
ctrl+z：将任务中止（暂停的意思），但是此任务并没有结束，它仍在进程中，只是维持挂起的状态。可以使用jobs命令来查看有什么程序是挂起的状态，可以使用fg %进程号来启动进程。

TIME_WAIT状态，需要服务器与客户端都已经退出来才会出来。
- 服务器端尽可能使用SO_REUSEADDR
- 在绑定之前尽可能调用setsockopt来设置SO_REUSEADDR套接字选项
- 使用SO_REUSEADDR选项可以使得不必等待TIME_WAIT状态消失就可以重启服务器。

在添加了多进程并发访问服务器的机制后，要记得把子进程的给退出exit了。当然你整个服务器关闭它也会关闭。关闭整个服务器有时候代价有点大。你总不能把不用的子进程一直开着吧。
可以使用
ps -ef |grep echosvr
进行查看echosvr的进程。你close后就发现，进程defunct掉了。
【更新】：理解错了。defunct也是没有完全关闭的意思。是指僵尸进程。
source:
概念：
什么是僵尸进程？
子进程退出时，内核将子进程置为僵尸状态，这个进程称为僵尸进程，它只保留最小的一些内核数据结构，以便父进程查询子进程的退出状态。（如果父进程没有查询子进程的退出状态，子进程是没有办法真正完全退出的。）
解决办法：
 父进程对子进程进行查询，查询它的退出状态，使用wait/waitpid函数。
 函数说明;
 wait:
NAME
       wait, waitpid, waitid - wait for process to change state

SYNOPSIS
       #include <sys/types.h>
       #include <sys/wait.h>

       pid_t wait(int *wstatus);
DESCRIPTION
       All of these system calls are used to wait for state changes in a child of the call‐ing process, and obtain information about the child  whose  state  has  changed. 
说白了就是：status参数是获得你等待子进程的信息，返回值是等待子进程的ID。
使用exit模拟正常退出，使用abort模拟非法退出。
系统宏：
| WIFEXITED(status)    |如果子进程正常结束，返回一个非零值     |
| --- | --- |
| WEXITSTATUS(stauts)    |如果WIFEXITED非零，返回子进程退出码     |

| WIFSIGNALED(status) |        进程因为捕获信号而终止        |
| ------------------ | ------------------------------- |
| WTERMSIG(status)    | 如果WIFSIGNALED非零，返回信号代码    |
| WIFSTOPPED(status)  | 如果子进程被暂停，返回一个非零值       |
| WSTOPSIG(status)    | 如果WIFSIGNALED非零，返回一个信号代码 |

waitpid：
NAME
       wait, waitpid, waitid - wait for process to change state

SYNOPSIS
       #include <sys/types.h>
       #include <sys/wait.h>

       pid_t wait(int *wstatus);
       pid_t waitpid(pid_t pid, int *wstatus, int options);

DESCRIPTION
       All of these system calls are used to wait for state changes in a child of the call‐ing process, and obtain information about the child  whose  state  has  changed.  
wait() and waitpid()：
       The wait() system call suspends execution of the calling process until  one  of  its children terminates.  The call wait(&wstatus) is equivalent to:
           waitpid(-1, &wstatus, 0);
pid=-1时，可以等待任意子进程。pid大于零时，等待特定子进程。总结：
pid == 0：等待其组ID等于调用进程的组ID的任一子进程。换句话说是与调用者进程同在一个组的进程。
pid < -1    :等待其组ID等于pid的绝对值的任一子进程。例如：pid=-100，则表示进程组ID=100里面的任一一个子进程。

wait和waitpid区别：
1.特定子进程和非特定子进程
2.在一个子进程终止前，wait使其调用者阻塞，而waitpid有一个选项，可以使调用者不阻塞。不阻塞的意思是，直接捕获当前的子进程的状态：
1.如果还没有子进程，则运行返回-1；
2.如果已经有子进程，但是没有退出，则返回0
3.如果已经有子进程，已经退出，处于僵尸状态，则返回子进程ID
然后继续运行。即使捕获。阻塞的意思是一直等待到捕获到僵尸状态的信息为止。
总结：
僵尸进程：
- 当一个子进程结束运行时，它与其父进程之间的关联还会保持到父进程正常地运行结束或者父进程调用了wait才结束
- 进程表中的代表进程的数据项是不会立刻释放的，虽然不再活跃了，可子进程还停留在系统里，因为它的退出码还需要保存起来以备父进程中后续的wait调用使用。
如何避免僵尸进程：
- 调用wait或者waitpid函数查询子进程退出状态，此方法父进程会被挂起
- 如果不想父进程挂起，可以在父进程中加入一条语句：signal(SIGCHLD，SIG_IGN);表示父进程忽略SGICHLD信号，该信号是子进程退出的时候向父进程发送的。


(source:p2psrv.c,p2pcli.c)在p2p聊天程序中，我发现，子进程上的printf中要输出的语句已经在缓存中了，在shell中，按方向键向上，会出现它的语句出来。
在使用信号signal来通知其他进程已经退出的时候，不是特定就是父进程告诉子进程，子进程告诉父进程的，是由实际例子中，大概率是处于什么状态突然退出，然后其他进程没能退出，才使用信号告诉它的。比如serve端，是父告诉子，因为大部分时间是在接收对方信息的状态（父进程），client是大部分时间等待对方信息是在子进程。

四、流协议和粘包
暂时还看不太明白。
TCP是一个流协议，也就是没有边界，或者说分不清数据的边界。TCP它并不知道哪一个是哪一个包，它只会根据自己的缓冲区的大小来分配和划分包，所以它可能把两个数据包打包成一个tcp包发送，也可能把一个数据包拆分成多个发送出去。这就是所谓的拆包和粘包。

假设客户端分别发送两个数据包D1和D2给服务端。由于服务端一次读取到的字节数不确定，可能存在4种情况。
- 服务端分别接收到 D1 和 D2.没有拆包和粘包。
- D1和D2包被一次接收了(粘包)
- D1包被一次接收，D2包被分两次接受(拆包)
- D1和D2都被拆开，分两次读取完成
- D1和D2被拆分N个，分N次读取完成.

产生的原因：
程序的写入的字节大于发送数据的缓冲区（MTU）大小
进行MSS大小的TCP分段
以太网帧的payload大于MTU进行IP分片

解决方案：
1.定长包：使发送的包是定长包，对等方就会以定长的方式进行接收，就确保了消息之间的边界了。
2.包尾加\r\n(ftp):识别\r\n作为消息的边界，这个会有一个问题就是如果数据包内本身就有这些字符的话，还得加上转义符。
3.包头加上包体的信息，比如包的长度
4.封装更为复杂的应用层协议：目的就是需要知道接收了多少长度的包，所以可以封装一个函数可以知道发送和接收多少包的函数。

注意：
上层应用write 多大 与底下协议栈发送多大没有必然联系。比如你快速连续发送两个tcp数据报 每个500字节 , 可能实际发出的是一个1000字节的数据报，除非你做了特殊设置。
TCP有个最大分节大小(MSS)选项可设置发送数据量的最大值，此值可设典型值为1024。一般数据包越大由于传输的次数减少，使得加在数据上的额外比特的比例降低，因而效率更高。但是由此也使得延时增加，需要更大buffer等问题，实际上数据包多大要根据发送数据类型，网络情况而定。比如你需要多次发送数据但每次数据量比较小，或数据实时性要求比较高，那么采用小的数据包更合适，反之需要一次发送大量数据，大的数据包效率更高，还有数据在以太网上传输和在光纤上传输，最合适的数据包大小也有区别。

五、粘包的解决方案具体实现
代码：
echosrv.c   echocli.c   封装应用层
echosrv1.c    echocli1.c    定长包

六、解决僵尸进程问题
souece:getlocalip.c,echosrvpro.c,echoclipro.c
getsockname：当客户端成功与服务端连接后，可以通过此函数获得客户端地址。
getpeername：获取对等方地址
gethostname：获取主机的名称
gethostbyname：获取主机上所有的ip地址
source:    getloacalip.c
解决僵尸进程的方案：
1.忽略SIGCHLD信号，所以加入
```
signal(SIGCHLD,SIG_IGN);
```
2.可以捕获SIGCHLD信号来进行忽略。
```
void handle_sigchld(int sig)
{
    wait(NULL);//捕获子进程的退出状态，由于不关心退出状态，所以传NULL
}
```
3.解决同时有很多个子进程同时退出，wait函数并不能等待所有子进程的退出，需要用到waitpid。这里的关键点是在一小段时间段内，同时有许多子进程需要退出，发送信号，同时进入处理函数中子进程只释放掉一个，和它一起进来的就忽略掉了，而不一起进来的，可以另外响应一次处理函数，所以它可能是一个随机的过程，比如有五个子进程，同时进入2个，只释放掉一个，另外三个都是一个一个一次进入处理函数的，也都释放掉了，只有一个没有，所以会有1个僵尸进程；如果同时进入5个子进程，只处理一个，那么就会有4个僵尸进程。所以，处理为：
```
void handle_sigchld(int sig)
{
    while(waitpid(-1,NULL,WNOHANG) > 0);
    /*
    1.如果还没有子进程，则运行返回-1；
    2.如果已经有子进程，但是没有退出，则返回0
    3.如果已经有子进程，已经退出，处于僵尸状态，则返回子进程ID>0
    所以同时进的话，可以循环处理掉，平常没有进程的时候，就直接退出掉。
    */
}
```


七、tcp的流程
客户端：                                    服务端：
                                                                LISTEN
SYN_SENT            ----------->                 SYN_RCVD
ESTABLISHED      ----------->                  ESTABLISHED

FIN_WAIT_1          ----------->                  CLOSE_WAIT 
FIN_WAIT_2          ----------->                  LAST_ACK
TIME_WAIT           ----------->                  CLOSE

以上有10种状态，还有一种比较特殊的状态（CLOSING：双方那同时关闭）。共11种状态。
可以分成两类：3次握手，四次挥手。

注意一个现象：
处于FIN状态中，往套接字中写是允许的，它代表它不再发送数据了，但是对方还是可以发送数据的。
其中说到了PIPE管道，但是还没有概念，暂时不先放着。

八、五种io模型
source:
severlet.c    clientlet.c    echosrvpro.c    echoclipro.c
1.阻塞IO
2.非阻塞IO
3.IO复用（select和poll）主要
4.信号驱动IO
5.异步IO
关于select：
旨在用来解决多个文件描述符冲突，比如想从键盘接收数据和网络接收数据这两个事件没有办法同时进行处理。现在的代码是：
fgets阻塞卡住等待键盘的输入，进不到socket的读入，所以读不到0，就到不了LAST_ACK这个状态，对等方就到不了TIME_WAIT这个状态。使用select就解决了阻塞的问题。哪一个io想要使用就使用。
NAME
       select, pselect, FD_CLR, FD_ISSET, FD_SET, FD_ZERO - synchronous I/O multiplexing

SYNOPSIS
       /* According to POSIX.1-2001, POSIX.1-2008 */
       #include <sys/select.h>

       /* According to earlier standards */
       #include <sys/time.h>
       #include <sys/types.h>
       #include <unistd.h>

       int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);

       void FD_CLR(int fd, fd_set *set);
       int  FD_ISSET(int fd, fd_set *set);
       void FD_SET(int fd, fd_set *set);
       void FD_ZERO(fd_set *set);

       #include <sys/select.h>

       int pselect(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, const struct timespec *timeout,const sigset_t *sigmask);

DESCRIPTION
       select() and pselect() allow a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O oper‐ation (e.g., input possible).  A file descriptor is considered ready if it is possi‐ble to perform a corresponding I/O operation.
总结：
select是一个管理者，可以管理多个IO，一旦其中一个io检测到我们感兴趣的事件，select函数就返回，返回值为检测到的感兴趣的事件数，并且返回那些事件发生了那些事件，进而处理事件。
       int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);
fd_set *readfds：表示一个集合，一个读的集合，如果检测到有读的桃姐口则放到这个集合中，一旦数据可读，select就可以返回。
fd_set *writefds：一个写的集合
fd_set *exceptfds：异常集合
struct timeval *timeout：超时时间。如果填写NULL则不会超时，一定会检测到事件后才返回；如果指定了超时时间，则在超时时间内还没有检测到事件，返回的事件个数等于0，另外的select返回失败为-1

这些集合需要配合一下宏进程操作：
void FD_CLR(int fd, fd_set *set);
将文件描述符fd从集合set中移除。
int  FD_ISSET(int fd, fd_set *set);
判定文件描述符fd是否在集合set中，注意：这个的set不是输入输出参数，是只读的
void FD_SET(int fd, fd_set *set);
将文件描述符fd添加到集合set当中
void FD_ZERO(fd_set *set);
清空集合
实例：
？？？为什么要写成int fd_stdin = fileno(stdio);
```
  fd_set rset;//声明一个可读的集合
    FD_ZERO(&rset);//将集合清空

    int nready;//检测到的事件个数

    //获得最大的文件描述符
    int maxfd;
    int fd_stdin = fileno(stdin);
    if (fd_stdin > sock)
        maxfd = fd_stdin;
    else
        maxfd = sock;

    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    while (1)
    {
        FD_SET(fd_stdin, &rset);
        FD_SET(sock, &rset);
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);

        if (nready == -1)
            ERR_EXIT("select");

        if (nready == 0)
            continue;

        if (FD_ISSET(sock, &rset))
        {//套接口产生了事件
            int ret = readline(sock, recvbuf, sizeof(recvbuf));
            if (ret == -1)
                    ERR_EXIT("readline");
            else if (ret == 0)
            {
                    printf("server close\n");
                    break;
            }

            fputs(recvbuf, stdout);
            memset(recvbuf, 0, sizeof(recvbuf));
        }
        if (FD_ISSET(fd_stdin, &rset))
        {//标准输入产生的事件
            if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL)
                break;
            writen(sock, sendbuf, strlen(sendbuf));
            memset(sendbuf, 0, sizeof(sendbuf));
        }
    }

    close(sock);
```
九、select实现并发
source:
severlet.c    clientlet.c    echosrvpro.c    echoclipro.c
理解概念：
- 并发：时间段内有很多的线程或进程在执行，但何时间点上都只有一个在执行，多个线程或进程争抢时间片轮流执行。遵循的原则是相应的调度算法。
- 并行：时间段和时间点上都有多个线程或进程在执行。
- 单核cpu的话只能是并发，多核cpu才能做到并行执行。

概述：
一旦检测到了多个事件，就需要一个个遍历它，一一处理这些IO事件，通常将用select实现的服务器称为并发服务器。
区别并行：当检测到多个IO事件后，实际上是无法并行处理这些IO事件的，select处理事件是按顺序执行的，所以它不是并行的。

读、写、异常事件发生条件
可读：
- 套接口缓冲区有数据可读
- 连接的读一半关闭，即接收到FIN段，读操作将返回0
- 如果是监听套接口，已完成连接队列不为空时
- 套接口上发生了一个错误待处理，错误可以通过getsockopt指定SO_ERROR选项来获取。

可写：
- 套接口发送缓冲区有空间容纳数据
- 连接的写一半关闭。即收到RST段之后，再次调用write操作
- 套接口上发生了一个错误待处理，错误可以通过getsockopt指定SO_ERROR选项来获取。

异常：
套接口存在带外数据

提问：有没有一个进程实现并发呢？
使用select来实现，因为它可以管理多个IO
主要的实现方法：维护一个集合，循环检测它是否有新的事件更新，有多个事件或一个事件都存进数组中，然后对这些更新的事件进行访问。
```
for(i = 0;i <= maxi;i++)
        {
            conn = client[i];
            if(conn == -1){
                continue;
            }

            if(FD_ISSET(conn,&rset)){
                char recvbuf[1024] = {0};
                int ret = readline(conn,recvbuf,1024);
                if(ret == -1){
                    ERR_EXIT("readline");
                }
                if(ret == 0){
                    //对方关闭
                    printf("client close\n");
                    FD_CLR(conn,&allset);   //从集合中移除该事件
                    client[i] = -1; //恢复默认值
                }

                fputs(recvbuf,stdout);
                write(conn,recvbuf,strlen(recvbuf));

                if(--nready <= 0){
                    break;
                }
            }
        }
```

十、严谨程序    close和shutdown的区别
1.close：关闭了读和写的两个管道
在父进程调用close时，只有当所有的进程都关闭了才发送FIN tcp字段。
2.shutdown：可以进行选择，关闭读或者写或者读写管道
NAME
       shutdown - shut down part of a full-duplex connection
SYNOPSIS
       #include <sys/socket.h>
       int shutdown(int sockfd, int how);
RETURN VALUE
       On  success,  zero is returned.  On error, -1 is returned, and errno is set appropriately.
how:
SHUT_RD—— 0    ：关闭读
SHUT_WR_—— 1    ：关闭写
SHUT_RDWR—— 2    ：关闭读写

shutdown与close不同的地方：
1.shutdown可以选择性关闭，close直接全部关闭
2.shutdown是使用就直接关闭，不会进行引用计数；close是进行进程的计数

十一、超时方法封装
source:timeout.c  timeoutcli.c
1.alarm：
使用alarm函数，进行定时，如果超时了，则会产生一个信号，进入到注册好的函数里面，这个函数主要是为了打断别的动作而已，所以不用做什么动作，直接return 0也可以。然后如果配合ret==-1,的话，就算为超时了。
```

void handler(int sig)
{
    return 0;
}
signal(SIGNALRM,handler);

alarm(5);
int ret = read(fd,buf,sizeof(buf));

if(ret == -1 && errno == EINTR)
{    
    //超时
    errno = ETIMEDOUT;
}
else if(ret >= 0)
{
    //证明在规定时间内读取到数据，关闭闹钟
    alarm(0);
}

```
问题：闹钟可能会作为其他的用途，这设置的闹钟跟其他用途的闹钟会产生冲突，解决这些冲突会有一些麻烦。

2.套接字选项
SO_SNDTIMEO:发送的超时时间
SO_RECVTIMEO:接收的超时时间
在setsockopt上的参数可以设置超时时间。
问题：存在移植兼容的问题。

3.select
read_timeout函数封装：

十二、select并发服务器
在使用select实现的并发服务器中，能达到的并发数，会受两方面限制。
1.一个进程能打开的最大文件描述符限制。调整内核参数。
2.select中的fd_set集合容量的限制（FD_SETSIZE，该宏默认是1024） ，这需要重新编译内核。
可以使用poll函数来解决。poll基本上和select差不多。只是没有文件描述符的限制。
十三、UDP
source:echosrvudp.c    echocliudp.c
1、无连接
UDP协议它内部并没有维护端到端的一些连接状态，这跟TCP是不同的，TCP是基于连接的，而在连接的时候是需要进行三次握手，而UDP是不需要的。

2、基于消息的数据传输服务
对于TCP而言，它是基于流的数据传输服务，而在编程时，会遇到一个粘包问题，是需要我们进行处理的，而对于UDP来说不存在粘包问题，因为它是基于消息的数据传输服务，我们可以认为，这些数据包之间是有边界的，而TCP数据包之间是无边界的。

3、不可靠
这里面的不可靠主要表现在数据报可能会丢失，还可能会重复，还可能会乱序，以及缺乏流量控制。

4、一般情况下UDP更加高效。

十四、聊天室程序

十五、域协议特点
十六、通信机制
[学习博客](https://www.cnblogs.com/webor2006/category/514056.html)


带宽的概念：
在网络中，带宽是指单位时间内能传输的数据量，也就是速度。单位：bit/s
其他的，在通讯和电子技术领域，是指频带宽度。单位：hz

单播：单播（Unicast）是在一个单个的发送者和一个接受者之间通过网络进行的通信。
- 单播的优点
1. 服务器及时响应客户机的请求
2. 服务器针对每个客户不同的请求发送不同的数据，容易实现个性化服务。
- 单播的缺点
1. 服务器针对每个客户机发送数据流，服务器流量=客户机数量×客户机流量；在客户数量大、每个客户机流量大的流媒体应用中服务器无法支持如此庞大的数据流。
2. 现有的网络带宽是金字塔结构，城际省际主干带宽仅仅相当于其所有用户带宽之和的5%。如果全部使用单播协议，将造成网络主干不堪重负。

广播：
网络广播应该说是一种网络流媒体，它通过在Internet站点上建立广播服务器，运行特定软件再把节目传播出去，我们通过在自己的计算机上安装和运行广播接收软件连接这些站点，然后就可方便地收听广播节目，还可阅读广播信息。
- 方式
网络广播有直播和点播两种主要播放形式：
A 直播（Live）：主要应用于重大活动的即时报道。它就是电台或电视台实际播出节目的网上传输形式，其优点是时效性强，生动实际，而且用户可在第一时间获取信息。
B 点播（On-demand Audio/Video）：点播是将节目根据内容做成一个个片段，你可根据标题或分类选择所喜爱的片段来收听收看。这种播放形式具有节约资源的优点，而且选择性和针对性也更强。

组播：还不太明白。