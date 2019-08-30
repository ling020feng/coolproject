### ffmpeg mac编译 ios记录

#### 步骤：

1、安装brew

2、安装ffmpeg

```
brew install ffmpeg
```

注意：如果提示安装jdk8，则需按提示安装



```
Error: An exception occurred within a child process:
  DownloadError: Failed to download resource "aom"
```

原因：新版ffmpeg4 更新aom依赖

解决方式：更新clang编译链



新版ffmpeg4 更新aom依赖

```
xcrun -sdk iphoneos clang is unable to create an executable file.
C compiler test failed.
```

原因：

1、系统安装了多个xcode环境，需要选定一个xcode

2、git版本太低

解决方式：xcode版本太低 编译更新到10



**> 更新xcode：（需要更新系统到macos10.14）**

1、申请AppStore 账号

2、完善账号信息（必须完善才能下载软件）

3、卸载原有xcode，下载最新xcode（v 10.x）

4、重启、安装

错误：

```
Error: You have not agreed to the Xcode license. Please resolve this by running:
  sudo xcodebuild -license accept
运行提示语句
```

**> 更新mac系统：系统设置中更新，然后在AppStore 中安装该版本最新**



**> 更新git 版本：指令如下**

```
brew install git 安装git
which git 查看git 路径
git --version 查看git版本
brew link git --overwrite git链接brew安装的git
```

注意：如果链接提示错误，需使用sudo或者给提示文件目录赋予权限，如下：

```
chmod + 777 path
```

