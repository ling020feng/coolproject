

#### 错误记录

**错误**

```
[armeabi-v7a] SharedLibrary  : libcloud.so
jni/CloudPlayback.c:386: error: undefined reference to 'danacloudinit'
jni/CloudPlayback.c:435: error: undefined reference to 'danacloudcachelimitswitch'
jni/CloudPlayback.c:147: error: undefined reference to 'danacloudreadvideo'
jni/CloudPlayback.c:240: error: undefined reference to 'danaclouddestroyavdata'
jni/CloudPlayback.c:279: error: undefined reference to 'danacloudreadaudio'
jni/CloudPlayback.c:325: error: undefined reference to 'unInitAudioCodec'
jni/CloudPlayback.c:337: error: undefined reference to 'initAudioDecode'
jni/CloudPlayback.c:340: error: undefined reference to 'audioDecode'
jni/CloudPlayback.c:353: error: undefined reference to 'danaclouddestroyavdata'
jni/CloudPlayback.c:359: error: undefined reference to 'unInitAudioCodec'
jni/CloudPlayback.c:501: error: undefined reference to 'danacloudwritestream'
jni/CloudPlayback.c:591: error: undefined reference to 'danaclouduninit'
clang++: error: linker command failed with exit code 1 (use -v to see invocation)

```

解决方式：

1、查看头文件路径是否引用正确

2、查看链接静态库是否缺失

3、库文件是否缺少链接

4、库文件类型是否匹配（编64位用的32位）



**错误**

```
[arm64-v8a] SharedLibrary  : libcloud.so
jni/libs/lib_danaeucvideo.a(danale__obj2): In function `_________danale_x9_F6':
(.text+0x24b4): undefined reference to `in6addr_any'
jni/libs/lib_danaeucvideo.a(danale__obj2): In function `_________danale_x9_F6':
(.text+0x24cc): undefined reference to `in6addr_any'
jni/libs/lib_danaeucvideo.a(danale__obj2): In function `_________danale_x9_F4':
(.text+0x2ee4): undefined reference to `in6addr_any'
jni/libs/lib_danaeucvideo.a(danale__obj2): In function `_________danale_x9_F4':
(.text+0x2f00): undefined reference to `in6addr_any'
jni/libs/lib_danaeucvideo.a(danale__obj2): In function `_________danale_x9_F5':
(.text+0x32b8): undefined reference to `in6addr_any'

```

原因：编译链平台最低版本libc库中未包含该变量，Google在api24进行了原生网络的修改

![1563335068256](/home/danale/.config/Typora/typora-user-images/1563335068256.png)

![1563335038126](/home/danale/.config/Typora/typora-user-images/1563335038126.png)

解决方式：修改平台版本为24

针对问题解决方案：

1、使用APP_PLATFORM := android-24（优先）

能够解决问题，但是库最低支持Android版本Android7.0

2、保持APP_PLATFORM := android-21不变，拷贝Android 24的libc库到本地。















