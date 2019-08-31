### Android 学习中遇到的问题汇总：

使用 Ubuntu Android studio 连不上真机

` adb devices                    `

问题如下 

```
List of devices attached 
????????????    no permissions
```

### 解决方法：

使用adb

步骤：

没有就安装

然后 终端输入 lsusb

> Bus 002 Device 002: ID 8087:8000 Intel Corp. 
> Bus 002 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
> Bus 001 Device 002: ID 8087:8008 Intel Corp. 
> Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
> Bus 004 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
> Bus 003 Device 003: ID 046d:c077 Logitech, Inc. M105 Optical Mouse
> Bus 003 Device 002: ID 046d:c31c Logitech, Inc. Keyboard K120
> Bus 003 Device 004: ID 18d1:4ee7 Google Inc. 
> Bus 003 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub

可以看到`Bus 003 Device 004: ID 18d1:4ee7 Google Inc. `

设备4 ID18d1 goole 是品牌

`vi /etc/udev/rules.d/51-android.rules `

修改为

```
SUBSYSTEM=="usb", ATTR{idVendor}=="18d1", ATTR{idProduct}=="4ee7", MODE="0660", 
GROUP="plugdev", SYMLINK+="android%n"
```

改成自己的型号

然后`adb devices` 

查看自己的设备型号

`0481b85b08cd2fd8	device`

**adb指令**

`sudo adb kill-server`

`sudo adb start-server`

`adv devices`

参考网址

 (devices)[https://askubuntu.com/questions/908306/adb-no-permissions-on-ubuntu-17-04]

### 思考

不同的手机调试，均需要重新启动adb，不然会读取不到手机设备