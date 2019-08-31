#########################################################################
# File Name: build.sh
# Author: lgw
# mail: gwacoe@163.com
# Created Time: 2019年07月05日 星期五 16时42分17秒
#########################################################################
#!/bin/bash
NDK=/home/danale/Android/android-ndk-r15c
#中间编译链每个架构都有不同的编译链
TOOLCHAIN=$NDK/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64
#最后的目录名不一样
PLATFORM=$NDK/platforms/android-21/arch-arm64

CROSS_COMPILE=$TOOLCHAIN/bin/aarch64-linux-android-
CFLAGS="-DANDROID -fPIC"
#绝对路径
PREFIX=$(pwd)/arm64_v8a
echo $NDK
echo $PREFIX

export CPPFLAGS="$CFLAGS"
export CFLAGS="$CFLAGS"
export CXXFLAGS="$CFLAGS"
export CXX="${CROSS_COMPILE}g++ --sysroot=${PLATFORM}"
export LDFLAGS="$LDFLAGS"
export CC="${CROSS_COMPILE}gcc --sysroot=${PLATFORM}"
export NM="${CROSS_COMPILE}nm"
export STRIP="${CROSS_COMPILE}strip"
export RANLIB="${CROSS_COMPILE}ranlib"
export AR="${CROSS_COMPILE}ar"

#编译链文件目录下bin中程序也不相同
./configure --prefix=$PREFIX --host=aarch64-linux --target=aarch64-linux


make clean
make -j4
make install
#mkdir $PREFIX
#mkdir $PREFIX/lib
#mkdir $PREFIX/include
#chmod 777 $PREFIX
#cp /usr/local/lib/*.a ./$PREFIX/lib
#cp /usr/local/lib/*.so ./$PREFIX/lib
#cp ./include/*.h ./$PREFIX/include
