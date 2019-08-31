### 导入三方库到Android 工程记录

#### 验证三方库是否可用：

**步骤过程**

1、新建Android工程

2、app下 的build.gradle 修改

```
 defaultConfig {
        ..
        ...
        testInstrumentationRunner "android.support.test.runner.AndroidJUnitRunner"
        ndk {
            abiFilters "armeabi-v7a", "x86", "armeabi","arm64-v8a"
        }
    }
```

android 下增加

```
 sourceSets {
        main {
            jniLibs.srcDirs = ['libs', 'libs/arm64-v8a','libs/armeabi-v7a']
        }
    }
```

3、build ，在生成的jniLibs目录下 加入需要架构的 so库

4、新建java，命名与库名相同

class 加入

```
 public native void my_Test_jni();//库中一个方法声明为native
 static {
        System.loadLibrary("你的库名字");
    }
```

5、在 activity 中调用该类

6、build ，System.loadLibrary("Danasearch") 没报错就代表成功

常见错误

```
 java.lang.UnsatisfiedLinkError: dalvik.system.PathClassLoader[DexPathList[[zip file "/data/app/com.danale.video.mp4-2/base.apk"],nativeLibraryDirectories=[/data/app/com.danale.video.mp4-2/lib/arm64, /data/app/com.danale.video.mp4-2/base.apk!/lib/arm64-v8a, /vendor/lib64, /system/lib64]]] couldn't find "libZbarjni.so"
```

这说明库导入不成功

解决方式：删除build 重新编译，重新导入

此类错误导入成功，但缺少依赖库

```
 java.lang.UnsatisfiedLinkError: dlopen failed: library "libiconv.so" not found
```

