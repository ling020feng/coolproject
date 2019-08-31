关键词：Ubuntu16.04 caffe cpu_only python2API

**安装Ubuntu16.04虚拟机**

在vmware中安装一个Ubuntu16.04虚拟机来使用caffe，这样如果安装出错只需要重装虚拟机.

虚拟机分配了4G内存，硬盘空间40G



**安装openCV**

安装openCV3以上的版本，自行百度，我忘了过程了，谁执行了请把过程在这里补上并push commit

３月３０日补充：[opencv3安装教程参考](https://www.cnblogs.com/feifanrensheng/p/8619539.html)

**安装git**

​	sudo apt-get install git

**安装caffe**

将caffe项目克隆到本地，建议克隆在~/Dev中（~/Dev作为你的开发文件夹使用）

​	进入~/Dev中，执行

​		git clone git://github.com/BVLC/caffe

​	克隆完成后 ls 可以看到caffe文件夹

​	![1553758506723](./picture/Screenshot_from_2019-03-29_09-41-32.png)

然后我们开始安装caffe的各种依赖库

```
	sudo apt-get install libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler
	sudo apt-get install libgflags-dev libgoogle-glog-dev liblmdb-dev
	sudo apt-get install --no-install-recommends libboost-all-dev
```

**编译caffe**

1.编辑Makefile.config以选择caffe的工作方式（即cpu_only以及支持的python版本（注：本教程安装的pythonAPI是python2版本，期待有人写一份python3版本）等等）

​	可以直接拷贝本文件夹中我已经编辑好的Makefile.config复制到~/Dev/caffe中

2.在caffe目录下执行编译：

​	sudo make all

​	sudo make test

​	sudo make runtest

​	看到下图你就成功安装caffe啦

![1553760224712](./picture/Screenshot_from_2019-03-28_16-03-29.png)

3.若编译出错，执行sudo make clean，逐个排除错误后跳转步骤2

**安装pyhton API（python2版本）**

​	1.ubuntu16.04已经默认安装python2.7，但是没有pip

​		命令行输入python可以进入,查看后用exit()退出

![1553760747415](./picture/Screenshot_from_2019-03-28_16-12-18.png)

​	2.安装pip：sudo apt-get install python-pip

​	3.安装caffe的python API需要先安装若干个依赖库，在/caffe/中的requirement.txt中已经给出，用fortran编辑器批量安装它们：

​		安装fortran编译器：sudo apt-get install gfortran

​		进入caffe本地仓的python：cd ~/Dev/caffe/python

​		再执行：for req in $(cat requirements.txt); do pip install $req --user; done

​	4.将caffe本地仓的python文件夹添加到环境变量：

​		sudo gedit ~/.bashrc

​		在文件末尾添加：export PYTHONPATH=＊＊＊＊/Dev/caffe/python:$PYTHONPATH

​		＊＊＊＊是你的~对应路径

​		使得环境变量生效：sudo ldconfig

​	5.编译python接口：

​		cd ~/Dev/caffe

​		make pycafe

​		执行完成后进入python，输入import caffe，如下图所示就说明成功了

![1553761727242](./picture/Screenshot_from_2019-03-28_16-27-27.png)

​		