### 使用cmake编译fisheye库过程记录

#### 步骤：

1、安装NDK、cmake工具

2、cmakelist 内容修改

3、修改fisheye3 build.gradle 中ndk内容（不加过滤会编译所有版本）

```
 ndk{
           abiFilters "armeabi-v7a","arm64-v8a"
        }
```

4、build-》build module fisheye3

5、fisheye3-》build-》intermediate-》bundle  可以找到需要的库

6、库放入testvr 实验 

#### 错误汇总：

**错误：cmake 版本不兼容**

解决方式：SDK manager-》 取消最新版cmake，安装老版cmake，本次使用cmake3.6

**错误：64位库导入运行崩溃**

```
signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x0
07-09 16:37:54.165 479-479/? A/DEBUG:     x0   0000000000000000  x1   0000000000000000  x2   0000000000000004  x3   0000000000000003
07-09 16:37:54.165 479-479/? A/DEBUG:     x4   0000007f78963000  x5   00000000ffffffff  x6   0000000000000001  x7   0000007f5bf2b4f0
07-09 16:37:54.165 479-479/? A/DEBUG:     x8   0000007f5d0ab018  x9   0000007f5bf2b4f0  x10  0000000000000001  x11  0000007f5c3700c0
07-09 16:37:54.165 479-479/? A/DEBUG:     x12  0000007f78923bc0  x13  0000000000000007  x14  0000000000000008  x15  0000000000000052
07-09 16:37:54.165 479-479/? A/DEBUG:     x16  0000007f5d0aaf08  x17  0000007f788e5db8  x18  0000007f5c3700c0  x19  0000000012e12f00
07-09 16:37:54.165 479-479/? A/DEBUG:     x20  0000007f74d67660  x21  0000007f5cc30400  x22  0000000000000438  x23  0000000000000000
07-09 16:37:54.165 479-479/? A/DEBUG:     x24  0000000000000000  x25  0000000000000000  x26  0000000000000000  x27  0000000000000000
07-09 16:37:54.165 479-479/? A/DEBUG:     x28  0000000000000000  x29  0000007f5bf2abf0  x30  0000007f5d092730
07-09 16:37:54.165 479-479/? A/DEBUG:     sp   0000007f5bf2abf0  pc   0000007f788e5dc0  pstate 0000000080000000

```

原因：pthread_mutex_lock 函数锁死，导致原因不详，可能是新版本内核函数优化

解决方式：传入参数结构体指针改为取地址，能正常运行

[内存crash](https://blog.csdn.net/zhangbijun1230/article/details/80599671)

Android 互斥锁死锁问题

[可能原因1](https://blog.csdn.net/work_msh/article/details/8470277)

