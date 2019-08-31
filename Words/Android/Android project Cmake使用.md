### Android project Cmake使用



步骤记录

* 新建工程 增加c++ support
* 编辑CmakeLists.txt，可以静态库使用 STATIC

```
cmake_minimum_required(VERSION 3.4.1)

# 编译出一个动态库 native-lib，源文件只有 src/main/cpp/native-lib.cpp
add_library( # Sets the name of the library.
             native-lib
             # Sets the library as a shared library.
             SHARED
             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )

# 找到预编译库 log_lib 并link到我们的动态库 native-lib中
find_library( # Sets the name of the path variable.
              log-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )
target_link_libraries( # Specifies the target library.
                       native-lib
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
```

查看build.gradle

```
android {
    ...
    defaultConfig {
        ...
        externalNativeBuild {
            cmake {
                arguments '-DANDROID_PLATFORM=android-9',
                          '-DANDROID_TOOLCHAIN=clang'
                // explicitly build libs
                targets 'gmath', 'gperf'
            }
        }
    }
    ...
}
```

参数解释 -DANDROID_PLATFORM 编译Android平台 clang是工具链，在这也可以指定编译标准，ndk中未指定abifilters，将会编译出各类库。

* build 生成Java类头文件,在app/build/intermediates目录下/classes        找到可能在Javac目录下 使用指令

  ```
  javah -jni com.danale.NDKTools (包名加类名)
  ```

  生成的.h文件拷贝到 main/jni 中

* 在jni中编写相对应的 jni编程 的.c文件 必须包含头文件

  ```
  #include "com_danale_NDKTools.h"
  ```

* 编写Android.mk

* 修改build.gradle

  ```
  android {
      compileSdkVersion 28
      defaultConfig {
         ...
          testInstrumentationRunner "android.support.test.runner.AndroidJUnitRunner"
          ndk {
  
              moduleName "ndkdemotest-jni"
              abiFilters "armeabi", "armeabi-v7a", "x86", "arm64-v8a"
  
          }
      }
      buildTypes {
         ...
          externalNativeBuild {
              ndkBuild {
                  path 'src/main/jni/Android.mk'
              }
          }
          sourceSets.main {
              jni.srcDirs = []
              jniLibs.srcDirs = ['src/main/jniLibs']
          }
      }
  ```

  

* build 后可以在build-》intermediates-》bundle-》debug-》jni-》找到各类编译的库

* 引用需在类中加入一下代码

  ```
  static {
          System.loadLibrary("ndkdemotest-jni");
      }
  ```

  