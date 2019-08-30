Android studio 调试

[参考网址](https://www.jianshu.com/p/416a5f1c4419)

##### 单步调试：

step execution point 

光标定位到调试的位置

step over

单步跳过，执行到下一行

step into 

跳过执行到下一行，会进入到方法内部

force step into

强制单步跳过 ，有类库方法也会进入

drop frame

中断执行，回跳到执行它的地方

force run to cursor

忽略存在的断点，跳转带光标所在的地方

evaluate expression

对一些表达式进行求值操作

#### 断点管理

return

重新来过

pause program

暂停执行

resume program

恢复运行或者是当前断点跳到下一个断点

stop 

关闭当时文件，退出调试，停止项目运行

view breakpoint

查看所有断点

mute breakpoint

禁用断点

get shread dump

获取线程dump 进入线程界面

show values inline

调试开启功能，会将代码右边显示变量

show method return vales

会在变量区显示返回值

