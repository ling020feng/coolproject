# 网络编程

---

### 主机序和网络序的问题

htons 把unsigned short类型从主机序转换到网络序

htonl 把unsigned long类型从主机序转换到网络序

ntohs 把unsigned short类型从网络序转换到主机序

ntohl 把unsigned long类型从网络序转换到主机序

在使用little endian的系统中，这些函数会把字节序进行转换；

在使用big endian类型的系统中，这些函数会定义成空宏；

字符转换：https://www.cnblogs.com/bluestorm/p/3168719.html

---

inet_network/inet_addr/inet_aton把点分式转换成主机序

说明：https://blog.csdn.net/f81892461/article/details/8578284

举例：https://blog.csdn.net/haicai1989/article/details/51424072

inet_aton & inet_ntoa & inet_addr和inet_pton & inet_ntop

说明：https://www.cnblogs.com/warren-liuquan/p/3555945.html

举例：https://blog.csdn.net/qq_42606051/article/details/81279605

---

#### setsockopt和select

+ https://blog.csdn.net/a493203176/article/details/65438182

  ---

+ 本地回环测试tcp

  nc -l 127.0.0.1 8888	//server

  nc 127.0.0.1 8888	  //client

  ---

  + inet_ntoa()使用与注意事项

    https://blog.csdn.net/weixin_38887666/article/details/80757131

  + recv错误码以及超时设置

    https://blog.csdn.net/hq354974212/article/details/76077635

  #### 非阻塞I/Oselect()DEMO

  https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_72/rzab6/xnonblock.htm

  注意：fcntl/ioctl非阻塞必须在select前面设置

  ---

  #### socket绑定的ip为INADDR_ANY的意义

  + https://blog.csdn.net/qq_26399665/article/details/52932755

---

+ 以下内容转载自gitlab of 周星宇

+++

- 大小端

大端:高地址对应低字节(TCP/IP的选择)

小端:高地址高字节

```
代码
```

- 主机字节序和网络字节序

在书中出现比较频繁,现在明晰下这个概念 

> 主机字节序:不同的CPU有不同的字节序类型
>
> 网络字节序是TCP/IP中规定好的一种数据表示格式，它与具体的CPU类型、操作系统等无关，采用大端排序方式。

```
htons 把unsigned short类型从主机序转换到网络序
htonl 把unsigned long类型从主机序转换到网络序
ntohs 把unsigned short类型从网络序转换到主机序
ntohl 把unsigned long类型从网络序转换到主机序


在使用little endian的系统中，这些函数会把字节序进行转换；
在使用big endian类型的系统中，这些函数会定义成空宏；
```

- 点分十进制和二进制转换函数

  - ipv4: 

  int inet_aton 转换成网络字节序二进制 (const char *strptr,struct  in_addr *addrptr)

  返回1 0

  char *inet_nota 转换成点分十进制 (struct in_addr inaddr)

  返回指针

  - ipv4和ipv6通用的转换函数

  inti inet_pton(int family,const char *strptr,struct  in_addr *addrptr) 

  成功返回1,无效地址0,出错-1

  const char*inet_ntop(int family,const void *addrptr,char *strptr,size_t len)

  返回指针

- size_t和ssize_t

为方便代码移植

> 注意 
>
> 32位机上int等同于long int
>
> 64位机上int为32 long int 为64位

ssize_t:符号整型

size_t :无符号整型

- socket(int familt,int type,int protocol)

  参数选项见图 <socket三个参数含义>

  > 创建套字节

- connect(int sockdf,const struct sockaddr *servaddr,socklen_t addrlen)

- bind(int sockfd,const struct sockaddr *myaddr,socklen_t addrlen)

绑定端口方便通讯

- accept(int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen)

返回连接描述符,错误为-1

- close(int sockfd)

- 端口号

服务端和客户端端口号的联系???