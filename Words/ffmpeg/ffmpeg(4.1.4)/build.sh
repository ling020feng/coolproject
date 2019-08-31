#########################################################################
# File Name: build.sh
# Author: lgw
# mail: gwacoe@163.com
# Created Time: 2019年07月27日 星期六 09时58分11秒
#########################################################################
#!/bin/bash

clear

#需要的Android程序支持的架构
#不要修改下面配置！！！
ANDROID_ARMV5_CFLAGS="-march=armv5te "
ANDROID_ARMV7_CFLAGS="-march=armv7-a -D__thumb__ -mthumb -mfloat-abi=softfp -mfpu=neon"
ANDROID_ARMV8_CFLAGS="-march=armv8-a -D__thumb__ "
ANDROID_X86_CFLAGS="-march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32"
ANDROID_X86_64_CFLAGS="-march=x86-64 -msse4.2 -mpopcnt -m64 -mtune=intel"

build()
{

NDK=/home/danale/Android/android-ndk-r17c
ARCH=$1			# arm arm64 x86 x86_64
CPU=$2 	# armeabi armeabi-v7a x86 mips
PREFIX=$(pwd)/android/$CPU
TOOLCHAIN=$NDK/toolchains/$3-4.9/prebuilt/linux-x86_64
SYSROOT=$NDK/platforms/android-21/$4
CROSS_PREFIX=$TOOLCHAIN/bin/$3-

echo ------------------------≧ω≦ start print configure ≧ω≦---------------------------
echo ANDROID_ARMV5_CFLAGS= $ANDROID_ARMV5_CFLAGS
echo ANDROID_ARMV7_CFLAGS= $ANDROID_ARMV7_CFLAGS
echo ANDROID_ARMV8_CFLAGS= $ANDROID_ARMV8_CFLAGS
echo ANDROID_X86_CFLAGS= $ANDROID_X86_CFLAGS
echo ANDROID_X86_64_CFLAGS= $ANDROID_X86_64_CFLAGS
echo arch= $ARCH
echo cpu= $CPU
echo prefix= $PREFIX
echo toolchain= $TOOLCHAIN
echo sysroot= $SYSROOT
echo cross_prefix= $CROSS_PREFIX
echo ------------------------≧ω≦ print configure end ≧ω≦----------------------------

./configure \
	--prefix=$PREFIX \
   --enable-shared \
   --enable-static \
   --disable-doc \
   --disable-asm \
   --disable-debug \
   --disable-ffmpeg \
   --disable-ffplay \
   --disable-ffprobe \
   --disable-postproc \
   --disable-avdevice \
   --disable-symver \
   --disable-stripping \
   --target-os=android \
   --enable-cross-compile \
    --enable-decoder=h264 \
    --enable-decoder=hevc \
    --enable-decoder=mjpeg \
    --enable-parser=hevc \
    --enable-parser=h264 \
    --enable-parser=mjpeg \
    --enable-demuxer=h264 \
    --enable-demuxer=hevc \
    --enable-demuxer=mjpeg \
    --enable-encoders \
    --enable-muxers \
   --cross-prefix=$CROSS_PREFIX \
   --arch=$ARCH \
   --sysroot=$SYSROOT \
   --extra-cflags="-I$NDK/sysroot/usr/include/$3 -isysroot $NDK/sysroot -fPIC -D__ANDROID_API__=21 -DANDROID -Wfatal-errors -Wno-deprecated $5" \
   --enable-neon
   make clean all
   make -j8
   make install 
}


# build armeabi
build arm armeabi arm-linux-androideabi arch-arm "$ANDROID_ARMV5_CFLAGS"

#build armeabi-v7a
build arm armeabi-v7a arm-linux-androideabi arch-arm "$ANDROID_ARMV7_CFLAGS"

#build arm64-v8a
build arm64 arm64-v8a aarch64-linux-android arch-arm64 "$ANDROID_ARMV8_CFLAGS"

#build x86
#build x86 x86 x86 arch-x86 "$ANDROID_X86_CFLAGS"

#build x86_64
#build x86_64 x86_64 x86_64 arch-86_64 "$ANDROID_X86_64_CFLAGS"

