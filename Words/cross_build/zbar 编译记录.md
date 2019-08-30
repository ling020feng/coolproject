#### zbar 编译记录

错误：

```
Makefile:2425: recipe for target 'install-am' failed
make[1]: *** [install-am] Error 2
make[1]: Leaving directory '/home/danale/Desktop/zbar-0.10'
Makefile:2419: recipe for target 'install' failed

```

原因：1、脚本中空格未消除

​			2、安装在源码目录（有些不能安装）

​			3、权限不足

错误

```
checking host system type... Invalid configuration  aarch64-linux-gnu': machineaarch64' not recognized
```

原因：老版没有该架构，需要更新 config.sub 和 config.guess 

解决方式：复制其他安装包的文件，或者输入指令获取最新文件

```
wget -O config.guess 'http://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.guess;hb=HEAD'

wget -O config.sub 'http://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.sub;hb=HEAD'
```



```
cstriker1407:/zbar/zbar-0.10$ /home/danale/Android/android-ndk-r15c/platforms/android-21/arch-arm64-gcc  ./configure  --disable-video --without-imagemagick --without-xv --without-xshm --without-gtk --without-python -without-qt  --disable-assert --build=x86_64 -host=arm-unknown-linux-uclibcgnueabi --disable-shared
```

configure --host=aarch64-linux CC=aarch64-linux-android-gcc --enable-shared --prefix=./arm64_v8a

[zbar各类库下载网址](https://github.com/chentao0707/ZBarAndroidSDK/tree/master/ZBarScanProjAll/libs)

[地址2](https://github.com/dm77/barcodescanner/tree/master/zbar/src/main/jniLibs/arm64-v8a)

