# 准备工作
一.首先应该看《开发环境指南》
配置好开发环境再进行开发。
我的开发环境是Ubuntu18，打算使用网口和串口和板子连接。
所需要的软件工具：交叉编译器、nfs、telnet

软件包的安装：
1.使用bash。ubuntu中默认使用的是dash。
更改命令
```
sudo dpkg-reconfigure dash
选择no
```
Ps：一开始的时候，我没注意需要更改为bash，所以在安装sdk的时候出现了一些奇怪的问题。
```
./sdk.unpack: 2: ./sdk.unpack: source: not found
./sdk.unpack: 4: ./sdk.unpack: ECHO: not found
./sdk.unpack: 6: ./sdk.unpack: WARN: not found
./sdk.unpack: 7: ./sdk.unpack: WARN: not found
./sdk.unpack: 8: ./sdk.unpack: ECHO: not found
./sdk.unpack: 15: ./sdk.unpack: ECHO: not found
./sdk.unpack: 20: ./sdk.unpack: ECHO: not found
./sdk.unpack: 22: ./sdk.unpack: run_command_progress_float: not found
./sdk.unpack: 24: ./sdk.unpack: ECHO: not found
./sdk.unpack: 26: ./sdk.unpack: run_command_progress_float: not found
./sdk.unpack: 28: ./sdk.unpack: ECHO: not found
./sdk.unpack: 30: ./sdk.unpack: run_command_progress_float: not found
./sdk.unpack: 32: ./sdk.unpack: ECHO: not found
./sdk.unpack: 34: ./sdk.unpack: run_command_progress_float: not found
```
我查看了sdk.uppack，发现好像按照正常的理解，逻辑好像没什么问题。看它的报错，source not found
我直接在外面试了source，好像没什么反应，ECHO是找不到。有点懵。
然后请教了同事，说是需要更改为bash。修改后就可以正常使用了。不知道为什么。。。。

2.安装软件包
sudo apt-get install make libc6:i386 lib32z1 lib32stdc++6 zlib1g-dev libncurses5-dev ncurses-term libncursesw5-dev g++ u-boot-tools:i386 texinfo texlive gawk libssl-dev openssl bc
安装的时候安装u-boot-tools:i386需要Depends: binutils:i386，就常规的安装它就行了。

3.创建/etc/ld.so.preload文件，并使用命令  echo "" > /etc/ld.so.preload
目的是：解决64bit linux server上某些第三方库编译失败的问题。——————————如何解决？？？？

4.安装gperf工具，下载地址http://ftp.gnu.org/pub/gnu/gperf/gperf-3.1.tar.gz
功能：GNU 'gperf' generates perfect hash functions.

5.安装mtd-utils2.0.2
mtd-utils2.0.2 依赖以下几个库，以 ubuntu 为例，安装方式请参考下面命令：
sudo apt-get install zlib1g-dev liblzo2-dev uuid-dev pkg-config
由于 mtd-utils2.0.2 通过 pkg-config 工具检查各个库是否正常安装，因此请参考如下方
式设置 pkg-config 工具搜索路径：
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/lib/x86_64-linuxgnu/pkgconfig"
mtd-utils2.0.2 依赖于 automake1.15.1 版本，请参考如下方式安装 automake1.15.1 版本：
删除原有 automake 版本
sudo apt-get autoremove automake
下载 1.15.1 版本
− Windows 系统中使用浏览器访问 automake 工程 url 并下载对应源码包：
https://lists.gnu.org/archive/html/info-gnu/2017-06/msg00007.html；
− linux 系统中可以使用下面命令下载：
wget ftp://ftp.gnu.org/gnu/automake/automake-1.15.1.tar.gz
 编译安装 automake1.15.1
tar zxvf automake-1.15.1.tar.gz
cd automake-1.15.1/
./configure
make
make install

它到底有什么用？在哪起了作用？

二、安装交叉编译工具
参考《开发环境指南》、《linux SDK安装以及升级》
装好后，环境变量需要设置一下。以下这个命令只能针对当前终端下有用。
source /etc/profile
如何全局有用，需要查查。
如果没有设置环境变量，那么再使用到交叉编译工具的时候就会出错，需要注意一下。
1.解压
tar -xvf arm-himixXXX-linux.tgz
2.安装
sudo ./arm-himixXXX-linux.install
途中发生一些神奇的问题：
```
Installing HuaWei LiteOS Linux at /opt/hisi-linux/x86-arm
mkdir: created directory '/opt/hisi-linux/x86-arm/arm-himix100-linux'
Extract cross tools ...
tar: /home/danale/Documents/Hi3516E: Cannot open: No such file or directory
tar: Error is not recoverable: exiting now
skip export toolchains path
tar (child): /home/danale/Documents/Hi3516E: Cannot open: No such file or directory
tar (child): Error is not recoverable: exiting now
tar: Child returned status 2
tar: Error is not recoverable: exiting now
```
分析的过程是：
查看了那个脚本
```
#!/bin/bash

TOP_DIR=/opt/hisi-linux/x86-arm
if [ -n "$1" ]
then
	[ -d "$1" ] && TOP_DIR=$1
fi

TOOL_DIR=$TOP_DIR/arm-himix100-linux
TAR_BIN_DIR=$TOOL_DIR/bin
TOOLS_PKG="$PWD/arm-himix100-linux.tar.bz2"
RUNTIME_LIB_PKG="$PWD/runtime_uclibc.tgz"

set +e

echo "Installing HuaWei LiteOS Linux at $TOP_DIR"

mkdir -pv $TOP_DIR

if [ -d $TOOL_DIR ]
then
	echo "Delete exist directory..." >&2
	rm $TOOL_DIR -rf 
else
	mkdir -pv $TOOL_DIR
fi

echo "Extract cross tools ..." >&2
tar -xf $TOOLS_PKG -C $TOP_DIR

# creat link

sed -i  '/\/arm-hisiv610-liteOS\//d' /etc/profile

if [ -z "`grep "$TAR_BIN_DIR" < /etc/profile`" ] ;
then
	echo "export path $TAR_BIN_DIR" >&2
	cat >> /etc/profile << EOF

# `date`
# HuaWei LiteOS Linux, Cross-Toolchain PATH
export PATH="$TAR_BIN_DIR:\$PATH" 
# 

EOF
        source /etc/profile
else
	echo "skip export toolchains path" >&2
fi


tar -xzf $RUNTIME_LIB_PKG -C $TOOL_DIR

```
是在echo "Extract cross tools ..." >&2
之后发生的错误。那就是tar -xf $TOOLS_PKG -C $TOP_DIR这条命令出错的。TOOLS_PKG="$PWD/arm-himix100-linux.tar.bz2"TOP_DIR=/opt/hisi-linux/x86-arm。
应该可以分析出这个命令出错了。TOP_DIR应该没错。应该可以分析出TOOLS_PKG，但是被Hi3516E迷惑了，怎么也想不通。然后请教周大佬才懂，我的文件夹上有空格，就是PWD上出错了。它是这样的
Documents/Hi3516E V200R001C01SPC010
一直没有注意到，E V之间是有空格的。然后它只读到了空格之前，所以就出现了Hi3516E的情形。


三、sdk
《linux SDK安装以及升级》
1.首先需要SDK包，在/home/danale/Documents/Hi3516E V200R001C01SPC010/软件包/Hi3516EV200R001C01SPC010/01.software/board/Hi3516EV200_SDK_V1.0.1.0里面，它包含了drv、mpp、osal、osdrv这些
使用bash。ubuntu中默认使用的是dash。
更改命令
```
sudo dpkg-reconfigure dash
选择no
```
Ps：一开始的时候，我没注意需要更改为bash，所以在安装sdk的时候出现了一些奇怪的问题。
```
./sdk.unpack: 2: ./sdk.unpack: source: not found
./sdk.unpack: 4: ./sdk.unpack: ECHO: not found
./sdk.unpack: 6: ./sdk.unpack: WARN: not found
./sdk.unpack: 7: ./sdk.unpack: WARN: not found
./sdk.unpack: 8: ./sdk.unpack: ECHO: not found
./sdk.unpack: 15: ./sdk.unpack: ECHO: not found
./sdk.unpack: 20: ./sdk.unpack: ECHO: not found
./sdk.unpack: 22: ./sdk.unpack: run_command_progress_float: not found
./sdk.unpack: 24: ./sdk.unpack: ECHO: not found
./sdk.unpack: 26: ./sdk.unpack: run_command_progress_float: not found
./sdk.unpack: 28: ./sdk.unpack: ECHO: not found
./sdk.unpack: 30: ./sdk.unpack: run_command_progress_float: not found
./sdk.unpack: 32: ./sdk.unpack: ECHO: not found
./sdk.unpack: 34: ./sdk.unpack: run_command_progress_float: not found
```
我查看了sdk.uppack，发现好像按照正常的理解，逻辑好像没什么问题。看它的报错，source not found
我直接在外面试了source，好像没报错，ECHO是找不到。有点懵。
然后请教了同事，说是需要更改为bash。修改后就可以正常使用了。不知道为什么。。。。

2.编译osdry
osdry里面有：
opensource——linux内核源码放在里面
tools/pc/mkyaffs2image——yaffs2utils文件系统
tools/board/gdb——gdb-7.9.1调试工具
tools/board/gdb——ncurses-6.0提供字符终端处理库
tools/pc/cramfs_tool——util-linux-2.31

Ncurses 提供字符终端处理库，包括面板和菜单。
util-linux 是一个开放源码的软件包，是一个对任何Linux系统的基本工具套件。含有一些标准 UNIX 工具，如 login。当开发停滞时，一群人创建了复刻util-linux-ng（ng意为“下一代”），但截至2011年1月已更名回util-linux，目前是包的正式版本。
Util-linux 软件包包含许多工具。其中比较重要的是加载、卸载、格式化、分区和管理硬盘驱动器，打开 tty 端口和得到内核消息。

可以单独进行编译，我一开始是单独进行编译，但是途中蹦出了许多问题。readme中说的是单独编译的话，文件系统不能保证能用，但是我在gdb编译的时候就出错了。让我来屡屡。
现在成功编译的是：全部编译
在osdrv中，就有Makefile，可以直接make all，来执行一系列的操作。但是会有一些坑。
首先，我一开始make all的时候，报了一些错，可能的原因：
1.我之前是分开编译的，已经弄了一些文件出来，可能一些操作不规范，冲突了，导致总的make all的时候出错
需要的操作是make OSDRV_CROSS=arm-himix100-linux clean，然后再重新make all
2.之后我看到有说权限不够的字眼，有点混乱，不知道是为什么会出现这个了，然后就加上了sudo make all，这时候会出现
arm-himix100-linux-gcc:command not found什么的，大概就是找不到这个命令。
这是因为超级权限的环境变量和普通用户的环境变量不一样，也就是我正常的
arm-himix100-linux-gcc hi.c      ——————正常编译
sudo arm-himix100-linux-gcc hi.c    ——————command not found
不能全局使用这个命令。如果需要在超级权限中使用，应该是要加入超级权限的环境变量的
但是使用tab键也可以补全，不能根据能不能使用tab来判断能不能在全局来找到这个命令。
解决办法也是先把clean掉，要clean干净，而且make clean的时候也不要加sudo，如果不需要的话。再进行make all就行了。
3.我的是又报了缺少bison这个东西，但是报的是warning，刚开始没有注意，后面的报的是
recipe for target 'd-exp.c' failed
recipe for target 'gdb-install' failed
还有找不到gdb/gdb这个文件找不到，hitool这个东西找不到。
就不知道怎么搞，又百度又是什么的，解决不了。然后就想先解决这个warning，sudo apt-get install  bison安装成功。
然后clean，再make all试试就成功了。莫名其妙就成功了。
之前分开编译，在编译gdb的时候，报的错误和make all全部编译的报出的错误一样在关于gdb的时候，最后解决的时候好像和gdb又没有什么关系。暂时不知道为什么。。。。。。
在安装bison的时候，装了这些东西，可能可以用来分析一下：
```
Reading package lists... Done
Building dependency tree       
Reading state information... Done
The following additional packages will be installed:
  libbison-dev
Suggested packages:
  bison-doc
The following NEW packages will be installed:
  bison libbison-dev
0 upgraded, 2 newly installed, 0 to remove and 84 not upgraded.
Need to get 605 kB of archives.
After this operation, 1,811 kB of additional disk space will be used.
Do you want to continue? [Y/n] y
Get:1 http://cn.archive.ubuntu.com/ubuntu bionic/main amd64 libbison-dev amd64 2:3.0.4.dfsg-1build1 [339 kB]
Get:2 http://cn.archive.ubuntu.com/ubuntu bionic/main amd64 bison amd64 2:3.0.4.dfsg-1build1 [266 kB]
Fetched 605 kB in 4s (151 kB/s)
Selecting previously unselected package libbison-dev:amd64.
(Reading database ... 212624 files and directories currently installed.)
Preparing to unpack .../libbison-dev_2%3a3.0.4.dfsg-1build1_amd64.deb ...
Unpacking libbison-dev:amd64 (2:3.0.4.dfsg-1build1) ...
Selecting previously unselected package bison.
Preparing to unpack .../bison_2%3a3.0.4.dfsg-1build1_amd64.deb ...
Unpacking bison (2:3.0.4.dfsg-1build1) ...
Setting up libbison-dev:amd64 (2:3.0.4.dfsg-1build1) ...
Processing triggers for man-db (2.8.3-2ubuntu0.1) ...
Setting up bison (2:3.0.4.dfsg-1build1) ...
update-alternatives: using /usr/bin/bison.yacc to provide /usr/bin/yacc (yacc) in auto mode
```
GNU bison 是属于 GNU 项目的一个语法分析器生成器。Bison 把一个关于“向前查看 从左到右 最右”(LALR) 上下文无关文法的描述转化成可以分析该文法的 C 或 C++ 程序。它也可以为二义文法生成 “通用的 从左到右 最右” (GLR)语法分析器。

成功：
---------finish osdrv work
CHIP:hi3516ev200(default) or hi3516ev300 or hi3518ev300 or hi3516dv200  换型号
---------finish osdrv work
make: *** No rule to make target 'CHIP:hi3516ev300'.  Stop.



四、烧写sdk
1.如果板子上没有网口，或者也没有uboot，那么就只能使用HiTool，参考《HiBurn 工具使用指南》
2.如果有uboot，有网口更好。就可以进行非常方便的烧写。参考《Linux SDK安装以及升级》
- 进入uboot进行配置ip与主机通信
- setenv serverip 设置服务端的ip   setenv ipaddr设置本地的ip（还有一些其他的配置）
- 这样就可以通过tftp进行烧写了。

现在是以16M的flash为例。分配为：
1M：uboot        4M：kernel        11M：rootfs
1.烧写uboot（这里是spi nor flash）
[这里贴uboot的一些命令](https://blog.csdn.net/cgzhello1/article/details/7850685)
[spi_flash](https://blog.csdn.net/qingzhuyuxian/article/details/83048539)
这里列出用到的：
erase start end
      - erase FLASH from addr 'start' to addr 'end'
mw 用指定的数据填充内存
参数 mw.b [address value ] //按字节显示
mw.w [address value ] //按字显示 
mw.l [address value ] //按长字显示 

sf probe [[bus:]cs] [hz] [mode] -    init flash device on given SPI bus and chip select
sf erase    擦除指定位置,指定长度的flash内容, 擦除后内容全1
sf write addr offset len             - write `len' bytes from memor at `addr' to flash at `offset'

1.烧写uboot
mw.b 0x42000000 0xff 0x80000
tftp 0x42000000 u-boot- hi3516ev200.bin
sf probe 0;sf erase 0x0 0x80000;sf write 0x42000000 0x0 0x80000
2.烧写内核
mw.b 0x42000000 0xff 0x400000
tftp 0x42000000 uImage_hi3516ev300
sf probe 0;sf erase 0x100000 0x400000;sf write 0x42000000 0x100000 0x400000
3.烧写文件系统
mw.b 0x42000000 0xff 0xb00000
tftp 0x42000000 rootfs_hi3516ev200_64k.jffs2
sf probe 0;sf erase 0x500000 0xb00000;sf write 0x42000000 0x500000 0xb00000
4.设置启动参数（注意 linux-4.9.y kernel 默认文件系统只读，需要在 bootargs 中加入rw 选项，文件系统才可读写）
setenv bootargs 'mem=32M console=ttyAMA0,115200 root=/dev/mtdblock2 rootfstype=jffs2 rw mtdparts=hi_sfc:1M(boot),4M(kernel),11M(rootfs)'
setenv bootcmd 'sf probe 0;sf read 0x42000000 0x100000 0x400000;bootm 0x42000000'
saveenv
切不可跳过第四步，我跳过了第四步想看看结果，然后就会运行到：
Starting kernel...
一直过不去，然后百度查到会有很多情况很多问题导致进入到这个。这个就是uboot刚结束想进入内核，但是不知道出于什么原因，不知道是进入了，但是串口没有反馈还是根本就没有进去！按照网上的一些教程说有可能是调试串口出问题了，要进入进行设置，然后重新生成.config再编译内核。结果还是一样。所以我又重新走了一遍流程，结果就ok了。所以不要做傻事，跳过某一步。
5.reset重启
6.其他nand flash、emmc请参考文档。


五、使用sdk和demo板进行开发
1.设置网络，为了可以和主机进行nfs交互(暂时只设置了ip)
- 设置ip ifconfig eth0 xxx.xxx.xxx.xxx
- ping 主机ip ————看ping得通吗
2.挂载nfs
- 在服务器上开设nfs服务器
- mount -t nfs -o nolock -o tcp -o rsize=32768,wsize=32768 xx.xx.xx.xx:/your-nfs-path /mnt
- 在/mnt目录下对服务器进行访问了
3.网络正常后，运行命令 telnetd& 就可以启动单板 telnet 服务，然后才能使用 telnet 登录到单板。
4.运行mpp业务
- 使用nfs，把mpp 拷贝到nfs服务器文件目录上，使板端可以访问到mpp
- 进入mpp/ko,加载相应的驱动，以3516ev300为例：  /load3516ev300 -i –sensor0 imx307 -osmem 32M
- 在sample文件目录下，进行make（交叉编译），生成执行文件，现在就可以在板端进行运行了。

一些问题：
为什么选择这个版本？有什么讲究吗？
为什么选择这个文件系统？选择的依据是什么？
打补丁的目的是什么？



