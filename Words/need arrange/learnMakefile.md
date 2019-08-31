# first
- 预处理器：将.c 文件转化成 .i 文件，使用的 gcc 命令是：gcc –E，对应于预处理命令 cpp；
- 编译器：将.c/.h 文件转换成.s 文件，使用的 gcc 命令是：gcc –S，对应于编译命令 cc –S；
- 汇编器：将.s 文件转化成 .o 文件，使用的 gcc 命令是：gcc –c，对应于汇编命令是 as；
- 链接器：将.o 文件转化成可执行程序，使用的 gcc 命令是： gcc，对应于链接命令是 ld；
- 加载器：将可执行程序加载到内存并进行执行，loader 和 ld-linux.so。

make/makefile是在大工程问题中，方便开发者进行编译链接成目标文件的一个工具。
在生成目标文件过程，比如说可执行文件，会经历预处理、编译、（汇编）、链接、（加载）的过程。
每个源文件经历了编译的过程后，就会生成一个中间件（.obj、.out），各个中间件链接起来生成目标文件。
基于这个过程，makefile的基本方法就是，目标文件（target）需要哪些中间件（依赖），这些中间件又是需要哪些库、函数（依赖），怎么通过这些依赖生成的（命令）。
大体上是这么回事，剩下的是他的一些为了简便工程所做出的操作。

所以，其实是可以通过命令行来全部实现的。但是，管理和修改工程的过程中会十分的麻烦。所以，makefile就出来了。

#### 通过命令行来生成
[先明确gcc的命令](https://www.runoob.com/w3cnote/gcc-parameter-detail.html)
-c：只激活预处理,编译,和汇编,也就是他只把程序做成obj文件
-o：为生成的“东西”重命名，如果没有这个参数，按照.out为后缀这个来命名。

```
gcc -c add/add_int.c -o add/add_int.o
```
[学习网站](https://my.oschina.net/u/2990965/blog/777627)
[学习网站](https://seisman.github.io/how-to-write-makefile/introduction.html#id4)
#### 初始版本的Makefile
```
#target exe
exe:main.o add_int.o add_float.o sub_int.o sub_float.o
        gcc -o exe ../add/add_int.o ../add/add_float.o ../sub/sub_int.o \
                ../sub/sub_float.o ../main.o

#get add_int.o
add_int.o:../add/add.h ../add/add_int.c
        gcc -c ../add/add_int.c -o ../add/add_int.o

#get add_float.o
add_float.o:../add/add.h ../add/add_float.c
        gcc -c ../add/add_float.c -o ../add/add_float.o

#get sub_int.o
sub_int.o:../sub/sub.h ../sub/sub_int.c
        gcc -c ../sub/sub_int.c -o ../sub/sub_int.o

#get sub_float.o
sub_float.o:../sub/sub.h ../sub/sub_float.c
        gcc -c ../sub/sub_float.c -o ../sub/sub_float.o
#get main.o
main.o:../main.c ../add/add.h ../sub/sub.h
        gcc -c ../main.c -o ../main.o -I../add -I../sub

#clean project
clean:
        rm -f exe ../add/add_int.o ../add/add_float.o \
                ../sub/sub_int.o ../sub/sub_float.o ../main.o

```

#### 使用用户自定义变量
```
CC = gcc
CFLAGS = -Iadd -Isub -O2
OBJS = add/add_int.o add/add_float.o sub/sub_float.o sub/sub_int.o main.o
TARGET = cacu
RM = rm -f

$(TARGET):$(OBJS)
        $(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS):%o:%c
        $(CC) -c $(CFLAGS) $< -o $@

clean:
        $(RM) $(TARGET) $(OBJS)

```
NOTE：$(OBJS):%.o:%.c中 %.o:%.c 是将 $(OBJS) 中以 .o 结尾的文件替换成以 .c 结尾的文件。
其中 $< 和 $@ 是自动化变量,下面会介绍。

```
CC = gcc
CFLAGS = -I../add -I../sub -O2
OBJS = ../add/add_int.o ../add/add_float.o ../sub/sub_int.o \
       ../sub/sub_float.o ../main.o
TARGET = exe
RM = rm -f
$(TARGET):$(OBJS)
        gcc -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS):%o:%c

clean:
        $(RM) $(TARGET) $(OBJS)

```

GNU的make很强大，它可以自动推导文件以及文件依赖关系后面的命令，于是我们就没必要去在每一个 .o 文件后都写上类似的命令，因为，我们的make会自动识别，并自己推导命令。
只要make看到一个 .o 文件，它就会自动的把 .c 文件加在依赖关系中，如果make找到一个 whatever.o ，那么 whatever.c 就会是 whatever.o 的依赖文件。并且 cc -c whatever.c 也会被推导出来。

#### 使用预定义变量的Makefile

```
CFLAGS = -Iadd -Isub -O2
OBJS = add/add_int.o add/add_float.o \
 sub/sub_int.o sub/sub_float.o main.o
TARGET = cacu

$(TARGET):$(OBJS)
    $(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

clean:
    -$(RM) $(TARGET) $(OBJS)
```

#### 使用自动变量的Makefile
```
TARGET = exe
CFLAGS = -I../add -I../sub -O2
OBJS = ../add/add_int.o ../add/add_float.o ../sub/sub_int.o \
       ../sub/sub_float.o ../main.o

$(TARGET):$(OBJS)
        $(CC) -o $@ $^

$(OBJS):%o:%c
        $(CC) -c $< -o $@ $(CFLAGS)

clean:
        -$(RM) $(TARGET) $(OBJS)

```
还记得上面出现的 \$< 和 \$@ 吗？它们是Makefile中的自动变量，分别代表依赖项和目标项。

在大的系统中，通常存在很多目录，手动添加目录的方法不仅十分笨拙而且容易造成错误。
```
CFLAGS = -Iadd -Isub -O2
OBJSDIR = objs
VPATH = add:sub
OBJS = add_int.o add_float.o sub_int.o sub_float.o main.o
TARGET = cacu

$(TARGET):$(OBJSDIR) $(OBJS)
        $(CC) -o $(TARGET) $(OBJSDIR)/*.o $(CFLAGS)

$(OBJSDIR):
        mkdir -p ./$@

$(OBJS):%.o:%.c
        $(CC) -c $(CFLAGS) $< -o $(OBJSDIR)/$@

clean:
        -$(RM) $(TARGET)
        -$(RM) $(OBJSDIR)/*.o -r

```
 在填写依赖项中，需要填写依赖项并且还要能找到他，如果没有VPATH的话，使用
 $(OBJS):%.o:%.c      他是使用c来替换o，而这里的.o是OBJS中的.o，而他的.o是没有写路径的，所以如果没有VPATH是会报错的，找不到.c文件（依赖）。
```
CFLAGS = -Iadd -Isub -O2
VPATH = add:sub
OBJS = add_int.o add_float.o sub_int.o sub_float.o main.o
TARGET = cacu
$(TARGET):$(OBJS)
        $(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

clean:
        -$(RM) $(TARGET)
        -$(RM) $(OBJS)

```

 使用命令 make 编译扩展名为 .c 的 C 语言文件的时候，源文件的编译规则不用明确地给出。这是因为 make 进行编译的时候会使用一个默认的编译规则，按照默认规则完成对 .c 文件的编译，生成对应的 .o 文件。它执行命令 cc -c 来编译 .c 源文件。在 Makefile 中只需要给出需要重建的目标文件（一个 .o 文件），make 会自动为这个 .o 文件寻找合适的依赖文件（对应的 .c 文件），并且使用默认的命令来构建这个目标文件。


#### 递归make
对于规模比较大的程序，需要多个人在多个目录下进行开发。如果只用一个 Makefile 来维护就会比较麻烦，因此可以在每个目录下建立自己的 Makefile ，然后在总控 Makefile 中调用子目录的 Makefile 文件。


#### Makefile中的函数
- 获取匹配模式的文件名wildcard
- 模式替换函数patsubst
- 循环函数foreach

