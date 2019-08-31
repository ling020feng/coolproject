# gcc
SONSOR0_TYPE是怎么从makefile.param中读取的？
gcc常用命令：
-c：只激活预处理,编译,和汇编,也就生成obj文件
-S：只激活预处理和编译，就是指把文档编译成为汇编代码。
-E：只激活预处理，不生成文档，需要把他重定向到一个输出文档里。
-o：定制目标名称，缺省的时候gcc 编译出来的文档是a.out
-ansi：关闭gnu c中和ansi c不兼容的特性，激活ansi c的专有特性。
-Dmacro：相当于C语言中的#define macro
-Dmacro=defn：相当于C语言中的#define macro=defn
-Umacro ：相当于C语言中的#undef macro
-Idir：指定头文件路径。
-llibrary：指定库
-Ldir：定制编译的时候，搜索库的路径。
-g：指示编译器，在编译的时候，产生调试信息。
-static：此选项将禁止使用动态库，所以，编译出来的东西，一般都很大。
-share：此选项将尽量使用动态库，所以生成文档比较小，但是需要系统由动态库。
-O0 -O1 -O2 -O3：编译器的优化选项的4个级别，-O0表示没有优化,-O1为缺省值，-O3优化级别最高
-Wall：会打开一些很有用的警告选项，建议编译时加此选项。
-std：指定C标准，如-std=c99使用c99标准，-std=gnu99，使用C99 再加上 GNU 的一些扩展。
在sample中的makefile.param中，有：
CFLAGS += -DSENSOR0_TYPE=$(SENSOR0_TYPE)
这个就加上去了。
举个例子：
```
#include<stdio.h>

void main(){
    printf("hello man %d\n",queque);
}

sudo gcc -o hello hello.c -Dqueque=1
./hello 
hello man 1

```