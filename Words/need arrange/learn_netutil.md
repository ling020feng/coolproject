## dana_net_util注意点

---

+ 防止出现Broken pipe错误信息

\#ifdef __IOS__

​        ret = send(fd, sendBuf, sendbuf_len, SO_NOSIGPIPE);//IOS下屏蔽SIGPIPE信号，下同作用，不同环境

\#elif (defined  _WIN32) || (defined UCOS_II)

​        ret = send(fd, sendBuf, sendbuf_len, 0);

\#else

​        ret = send(fd, sendBuf, sendbuf_len, MSG_NOSIGNAL); 

\#endif

#### signal(SIGCHLD, SIG_IGN)和signal(SIGPIPE, SIG_IGN);

+ https://blog.csdn.net/xinguan1267/article/details/17357093

一个while里的读写操作最好读写分开

select(fd,&rset,&wset,NULL,&timeout);

if(FD_ISSET(fd,&wset))      

{//可写，写操作}

if(FD_ISSET(fd,&rset))     

{ //可读，读操作}

