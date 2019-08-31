目前试过了预装openCV和caffe,再装openpose失败
也试过了预装openCV,装openpose时候同时装caffe也失败了

4月１日：

目前我在虚拟机上安装openpose都失败了，直接在ubuntu系统下安装



**尝试安装成功的流程是**

自己安装opencv,　然后git clone openpose 的工程，在工程目录下建build文件，在文件中使用cmake，最后sudo make -j8．


**cmake的具体命令如下**

cmake -DOpenCV_INCLUDE_DIRS=/home/"${USER}"/softwares/opencv/build/install/include \
  -DOpenCV_LIBS_DIR=/home/"${USER}"/softwares/opencv/build/install/lib ..

cmake -DOpenCV_CONFIG_FILE=/usr/share/OpenCV/OpenCVConfig.cmake ..



各路径如果出错会导致cmaked的运行过程中出错或者会在最后的make过程中出错，报错的内容一般都会说某路径找不到，然后用find命令查找报错中出现的文件夹的位置或者更改文件中的内容


如果是依赖包的内容直接百度如何安装依赖包



**opencv的安装请参考教程https://www.cnblogs.com/feifanrensheng/p/8619539.html**


**有用的命令：**

在当前目录和子目录下查找对应文件名的路径：find -iname "文件名"

find: ‘./run/user/1000/gvfs’: Permission denied

./usr/include/opencv

./usr/include/boost/compute/interop/opencv

./usr/share/maven-repo/org/opencv

./usr/share/maven-repo/org/opencv/opencv

./usr/share/opencv

./usr/share/OpenCV

在某文件中查找某字符串并返回所在行：grep -n "字符串" 文件路径/文件名


![](/home/danale/Pictures/Screenshot from 2019-04-01 17-11-04.png)

cpu版本必须八核以上的处理器，make命令要用sudo make -j8

安装完成后阅读github上的openpose的官网的(quickstart)[https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/quick_start.md#quick-start]文件

运行image版本，注意哦，要在openpose文件目录下执行命令，不然会出现找不到路径的错误



最后的效果：

![](yuewenjun/安装openpose_cpu_only在Ubuntu16.4/picture/Screenshot_from_2019-04-01_19-46-52.png)

![](yuewenjun/安装openpose_cpu_only在Ubuntu16.4/picture/Screenshot_from_2019-04-01_19-47-06.png)
