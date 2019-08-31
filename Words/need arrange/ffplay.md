1.下载 ffmpeg-*.tar.gz

到 Ffmpeg 官网 https://ffmpeg.org/download.html 挑选你要升级到的版本，然后下载，比如作者下载的是 ffmpeg-4.0.tar.gz。

如果你需要用到ffplay, 需要再下载SDL的源码，http://libsdl.org/release/，作者下载的是SDL2-2.0.8.tar.gz

在编译之前先安装

sudo apt-get install libx11-dev

sudo apt-get install xorg-dev

不然会无法渲染SDL display



2.编译安装

需要先编译安装SDL，如下操作：

tar zxvf SDL2-2.0.8.tar.gz

cd SDL2-2.0.8

./configure --prefix=/usr/

make

make install

再编译安装ffmpeg:

tar -zxvf ffmpeg-4.0.tar.gz
cd ffmpeg-4.0
./configure --disable-x86asm --enable-shared --prefix=/usr/
make

make install



3.动态链接库
vi /etc/ld.so.conf
在最后加入：include /usr/lib
执行:ldconfig



4.为 Ffmpeg 加入环境变量

vi /etc/profile.d/apps-bin-path.sh
在PAHT变量后面加入以下内容:  :/usr/bin




5.使修改立即生效
source /etc/profile
执行 
ffmpeg -version

打印结果


试下ffplay, ffplay ***.h264.


--------------------- 
