#########################################################################
# File Name: build_x264.sh
# Author: lgw
# mail: gwacoe@163.com
# Created Time: 2019年07月03日 星期三 17时13分35秒
#########################################################################
#!/bin/bash

NDK=/home/danale/Android/android-ndk-r15c
#中间编译链每个架构都有不同的编译链
TOOLCHAIN=$NDK/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64
#最后的目录名不一样
PLATFORM=$NDK/platforms/android-24/arch-arm64

PREFIX=./arm64_v8a
echo $NDK
echo $TOOLCHAIN
echo $PLATFORM
echo $PREFIX
#编译链文件目录下bin中程序也不相同
function build_one
{
    ./configure \
         --prefix=$PREFIX \
         --enable-static \
         --enable-shared \
         --enable-pic \
         --disable-asm \
         --disable-cli \
         --host=arm-linux \
         --cross-prefix=$TOOLCHAIN/bin/aarch64-linux-android- \
         --sysroot=$PLATFORM \
 
}
build_one
make -j4
make install

# build armeabi
#PREFIX=./armeabi
#build_one
#make -j4
#make install

#build armeabi-v7a
#PREFIX=./armeabi-v7a
#build_one
#make -j4
#make install
#build x86
#PREFIX=./x86
#build_one
#make -j4
#make install
#build x86_64
#PREFIX=./x86_64
#build_one
#make -j4
#make install


