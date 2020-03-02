### Ubuntu 安装VMware

#### 1、下载VMware安装包

[网址如下](https://www.vmware.com/products/workstation-pro/workstation-pro-evaluation.html)

#### 2、进入下载目录添加权限

```
sudo chmod +x VMware-xxx.bundle
```

#### 3、执行安装

```
./VMware-xxx.bundle
```



#### 4、问题汇总

* 缺少GCC环境

    apt install gcc

* Before you can runVMware, several modules must be compiled and load

如果是更新内核后导致，重新安装就好了

如果是刚安装就提示，则需要下载新的补丁文件

* Build Essential

Built Essential包含对编译Ubuntu二进制安装包所需的所有包的引用。

```
sudo apt install build-essential
```

* 产品秘钥

  百度