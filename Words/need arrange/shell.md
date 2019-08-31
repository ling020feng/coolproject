# shell
[学习教程](https://www.jianshu.com/p/6df409eb8535)
命令行解释器，读取用户输入，执行命令。
shell的用户输入通常来自于终端（交互式shell），有的则来自于文件（或者称为shell脚本）
脚本是一种批处理文件的延伸，是一种纯文本保存的程序，一般来说计算机脚本程序是确定的一系列控制计算机运行操作动作的组合，在其中可以实现一定的逻辑分支。
脚本程序在执行的时候，是由系统的一个解释器，将一条条翻译成机器可识别的指令，并按程序顺序执行。因为脚本在执行时多了一道翻译的过程，所以它比二进制程序执行效率要稍低一些。
主要特性：
语法和结构通常比较简单；
学习和使用通常比较简单；
通常以简单修改程序的“解释”作为运行方式，而不需要“编译”
程序的开发产能你优于运行产能
极大地提高了系统管理员的工作效率。

bash功能可以分为两个部分：内部命令（shell自带的命令）和外部命令（linux系统中可执行的程序命令/bin  /sbin）


shell本地变量
概念：只对当前shell进程有效（对当前进程的子进程和其他shell进程无效）
语法：
设置：变量名=变量值（符号不能有空格）
删除：unset 变量名
输出：echo 变量名

```
$ test=1
$ echo test
1
$ unset test
$ echo test

```

环境变量
概念：环境变量名词，效果是执行一个命令去“环境变量”设置的目录中挨个去寻找该命令的可执行程序（两种结果：1找到了并执行，2找不到报错）。
语法：
export 变量名=变量值
注意：
1当环境变量在/etc/profile中申明后，对所有用户都有效
2在家目录中的.bashrc中申明后，对当前用户都有效
3需要执行source /ect/profile或者重启shell窗口才能生效。

局部变量
概念：函数中申明的变量，函数调用时创建，调用完毕后销毁
语法：local 变量名=变量值

位置变量
概念：指程序动态运行时动态传入参数
语法：sh 路径及文件名 参数1 ... 参数n
echo $1  /  ... /echo $n

vim a.sh进入编辑
```
#!/bin/bash
echo $1
echo $2
```
保存，运行脚本。
sh a.sh 10 20
结果是输出
10
20

第一个参数就传给$1，第二参数就传给$2

特殊变量
概念：系统定义的特殊含义的变量（预定义变量）
| 变量    |含义     |
| --- | --- |
|    $0 |     当前脚本的文件名  |
|     $n|     传递给脚本或函数的参数。n表示几个参数。|
|     $#|    传递给脚本或函数的参数个数 |
|     #*|      传递给脚本或函数的所有参数 |
|     $@|   传递给脚本或函数的所有参数。被双引号“”包含时，与$*稍有不同  |
|     $?|     上个命令的退出状态，或函数的返回值|
|     $$|     当前shell进程ID。对于shell脚本就是这些脚本所在的进程ID|


文件通配符
| 符号  |含义     |
| --- | --- |
|  *   | 匹配0个或多个任意字符    |
|   ？  | 匹配一个任意字符    |
|   [若干字符]  | 匹配括号中的一个字符    |


命令代换
概念：通过语法反引号或$(名称)实现先解析shell指令，再赋值给变量
```
danale@danale-pc:~$ date
2019年 07月 16日 星期二 18:10:39 CST
danale@danale-pc:~$ test=$(date)
danale@danale-pc:~$ echo $test
2019年 07月 16日 星期二 18:11:00 CST
```

算数代换
概念：通过$((1+1)),[1+1]进行算术代换
ps：在脚本文件中只能使用$(())
```
danale@danale-pc:~$ echo 1+1
1+1
danale@danale-pc:~$ echo $(1+1)
1+1: command not found

danale@danale-pc:~$ echo $((1+1))
2

```

shell流程控制（判断）
概念：通过test或[]可以测试一个条件是否成立
语法：
法一
test 值1 条件 值2
法二
[值1 条件 值2]
0-代表结果成立   1-代表结果不成立

数值测试
| 参数    |说明     |
| --- | --- |
| -eq    |等与则为真     |
|  -ne   |  不等于则为真   |
|  -gt   |    大于则为真 |
|   -ge|    大于等于则为真 |
|    -lt |   小于则为真  |
|    -le |   小于等于则为真  |

文件测试
| 参数    |说明     |
| --- | --- |
|  -e文件名   |如果文件存在则为真     |
|   -r文件名  |   如果文件存在且可读则为真  |
|  -w文件名   |  如果文件存在且可写则为真    |
|  -x文件名   |   如果文件存在且可执行则为真   |
|   -s文件名  |    如果文件存在且至少有一个字符则为真  |
|  -d文件名   |   如果文件存在且为目录则为真   |
|   -f文件名  |    如果文件存在且普通文件则为真  |

字符串测试
| 参数    |说明     |
| --- | --- |
|  =   |等于则为真    |
|   ！= |  不相等则为真|

```
danale@danale-pc:~$ test 5 -gt 3
danale@danale-pc:~$ echo $?
0
danale@danale-pc:~$ test 5 -gt 7
danale@danale-pc:~$ echo $?
1
```

if else语句
语法：
if 条件1
then 
    命令1
elif 条件2
then
    命令2
else
    命令
fi
```
#!/bin/bash
echo 'hello world'
SCORE=$1

if test $SCORE -ge 90
then
    echo '优秀'
elif test $SCORE -ge 80
then
    echo '良好'
elif test $SCORE -ge 70
then
    echo '一般'
elif test $SCORE -ge 60
then
    echo '及格'
elif test $SCORE -ge 0
then
    echo '不及格'
else
    echo '出大问题'
fi

```
```
#!/bin/bash
who=$(whoami)
if test $who!='root'
then
    echo 'wrong'
    echo $who
else
    echo 'right'
fi#!/bin/bash
who=$(whoami)
if test $who!='root'
then
    echo 'wrong'
    echo $who
else
    echo 'right'
fi
```

case语句
语法：
case $变量名 in
    "值1")
    #如果变量的值等于值1，则执行程序1
    ;;
    "值2")
    #如果变量的值等于值2，则执行程序2
    ;;
    ..
    *)
    #如果以上都不成立的话，则执行此程序
    ;;
    esac

目标：
执行脚本让用户输入
yes -install...
no -skin 
其他 -Please enter the correct option
```
#!/bin/bash

read -p "Please Input yes/no" Select_Id
case $Select_Id in
    "yes")
        echo 'installing...'
        ;;
    "no")
        echo 'skip'
        ;;
    *)
        echo 'Please enter the correct option'
        ;;
esac
```

shell循环
1.for循环
语法：
for  变量名 in 值1...值n
do
    命令
done


输出6个数
```
#~/bin/bash

for i in 1 2 3 4 5 6
do 
    echo $i
done

```
输出指定目录下的所有文件名
```
#!/bin/bash

cd $1
filenames=$(ls)

for name in $filenames
do
    echo $name
done
```

2.while
```
#!bin/bash

i=1
while test $i -le 10
do
    echo $i
    i=$(($i+1))
done

```


计划任务
概念：约定时间执行指定任务（或执行指定脚本文件）
举例：
1通过计划任务发布文章
2通过计划任务凌晨3点将测试服务器项目代码同步到线上服务器

使用方法：
1.通过命令 crontab -e 编写计划任务
2.按下i键编写，最后按下esc :wq 保存并退出

-- crontab 指令介绍 
usage:  crontab [-u user] file
    crontab [ -u user ] [ -i ] { -e | -l | -r }
        (default operation is replace, per 1003.2)
    -e  (edit user's crontab)  ---编写计划
    -l  (list user's crontab)   --- 查看计划
    -r  (delete user's crontab)   --- 删除计划
    -i  (prompt before deleting user's crontab) --- 删除计划前提示

|  项目   | 含义 | 范围 |
| ------ | --- | ---- |
| 第一个* | 分钟 | 0-59 |
| 第二个* | 小时 | 0-23 |
| 第三个* | 天数 | 1-31 |
| 第四个* | 月份 | 1-12 |
| 第五个* | 星期 | 0-7  |

|                         项目                         |     含义     |              例子               |
| --------------------------------------------------- | ----------- | ------------------------------ |
| ,                                                   | 代表不连续时间 | 0 8,12,16 * * * 每天8,12,16点执行 |
| -                                                   | 代表连续时间   | 0 5 * * 1-6 每周一到六 5点执行     |
| */n  | 代表间隔多长时间执行 |    */10 * * * *每隔10min执行 |             |                                |



