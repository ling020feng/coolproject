# mpp媒体处理开发软件
## 1mpp概述
作用：支持应用软件快速开发。
如何实现快速的：对应用软件屏蔽了芯片相关的复杂的底层处理，对应用软件提供MPI接口完成相应的功能。
可以实现的功能：输入视频捕获、H.265、H.264/jpeg编解码，视频输出显示、视频图像前处理（去噪、增强、锐化）、图像拼接、图像几何矫正、智能、音频捕获及输出、音频编解码。
主要功能简写：
VI：视频输入
vpss：视频处理
VEND：视频编码
VDEC：视频编码
VO：视屏输出
AVS：视频拼接
AI：音频输入
AO：音频输出
AENC：音频编码
ADEC：音频解码
REGION：区域管理

上图主要为：
1.从摄像头传感器输入经过VI模块（处理）进入VPSS进行一些视频图像的一些处理，处理过的数据流通过Region模块可以添加OSD，然后经过一些编码协议进行视频编码存储；或者经过视频输出经由HDMI接口输出显示。
2.多摄像头传感器输入经过VI模块（处理）进入VPSS进行一些视频图像的一些处理，出咯过的数据流再经AVS视频拼接成完整场景的视频，再进行视频编码。
3.麦克风进行音频输入，再进行音频编码
4.（经过处理）的音频码流经过音频解码经过音频输出模块由扬声器释放。

## 2.系统控制
2.1 系统控制的任务：根据芯片特性，完成硬件各个部件的复位以及初始化，同时负责完成MPP系统各个业务模块的初始化、去初始化以及管理MPP系统各个业务模块的工作状态、提供当前系统版本信息，提供大块物理内存管理等。
# 根据mpp的层级是在操作系统适配层之上，与驱动层同级，应用层之下，它这个系统控制是哪个层级的任务？

- 视频缓冲池：
功能：主要向媒体业务提供大块物理内存管理功能，负责内存的分配和回收，充分发挥内存缓冲池的作用。
目的：让物理内存资源在各个媒体处理模块中合理使用。
构成：一组大小相同、物理地址里阿奴的缓存快组成一个视频缓冲池。
使用：在系统初始化之前配置公共视频缓冲池。

## 3.视频输入
需要理解PIPE管道===》进程
重要的概念：
- 视频输入设备
视频输入设备支持若干种时序输入，负责对时序进行解析。
- 视频输入物理PIPE
视频输入PIPE绑定在设备后端，负责设备解析后的数据再处理。
- 视频输入虚拟PIPE
视频输入虚拟PIPE不绑定设备，负责其他模块或者用户发送过来的数据再处理。
- 视频物理通道
物理通道负责将最终处理后的数据输出到DDR，在真正将数据输出到DDR前，它可以实现裁剪等功能。
- PIPE的工作模式
VI和VPSS的工作模式
- 掩码
掩码用于指示VI设备的视频数据来源。
- 镜头畸变校正（LDC）
镜头畸变校正，一些低端镜头容易产生图像畸变，需要根据畸变成都对其图像进行校正
- DIS
DIS模块通过比较当前图像与前两帧图像采用不同自由度的防抖算法计算出当前图像在各个轴向上的抖动偏移向量，然后根据抖动偏移向量对当前图像进行校正，从而起到防抖的效果。
- BAS
Bayer scaling，即Bayer域缩放。
- 低延时
低延时指图像写出指定的行数到DDR后，VI上报一个中断，把图像发给后端模块处理，可以减少演示，且硬件会有机制保证图像是先写后读，不会出现读错误。
- 提前上报中断
提前上报终端指图像写出指定的行数到DDR后，VI上报一个中断，把图像发给后端模块处理，可以减少延时，但没有和低延时一样的硬件机制保证后端模块读图像不会出错。

分为四层：DEV层，PIPE层，PHY-CHN，EXT-CHN
经过摄像头传感器进入MIPI，然后一次进入以下层级。
我的设想是：一个PIPE就是一个管道，对应一个进程，对应一块硬件资源，VI这一模块就是负责应对进入不同“目的地”所做的预处理。


#### 视频输出VO
模块从内存相应的位置读取视频或者图形数据，并通过相应 的显示设备输出视频和图形。
我现在使用一块是EV300，有三个输出BT.1120,BT.656,LCD.查芯片手册，他们好像是同一个管脚复用的。不过BT16位数据位输出。
### 感觉它这个引脚复用，可以互相复用，就是



mpp是一系列的相对应海思芯片的接口函数，屏蔽了底层硬件。
可以从手册中看出VO模块，每块芯片所拥有的相应的输出端口；VENC编码模块，可以编码成不同协议的码流就可以进行传输，可以传输到pc上，再进行相应的工具进行解码。


#### 视频处理子系统
对具体图像做处理。所支持的功能有：
FRC（frame rate control）、CROP（裁剪）、sharpen（锐化）、3DNR（降噪）、Scale（大小改变）、像素格式更换、LDC（畸变校正）、Spread、固定角度旋转、任意角度旋转、鱼眼校正、Cover/Coverex、Overlayex、Mosaic(马赛克)、Mirror/Flip、HDR、Aspect Ratio、压缩解压
功能描述：
- GROUP：各group分时复用VPSS硬件资源，硬件依次处理各个组提交的任务。
- CHANNEL：分为物理通道和扩展通道。物理通道可以实现裁剪、缩放功能。扩展通道的输入是物理通道的输出，把处理后的图像设置成用户的目标分辨率。
- PIPE：VPSS组的管道，取值只有0
- FRC：帧率控制，分为两种：组帧率控制（用于控制各GROUP对输入图像的接收）和通道帧率控制（用于控制各个物理通道和扩展通道图像图像的处理）。
- CROP：裁剪：组裁剪（VPSS对输入图像进行裁剪）、物理通道裁剪（VPSS对各个物理通道的输出图像进行裁剪）和扩展通道裁剪（VPSS调用VGS对扩展通道的输出图像进行裁剪）。
- Sharpen：对图像进行锐化处理。
- 像素格式转换：
- Scale：缩放
- Mirror/Flip：水平镜像
- Mosaic：马赛克
- Cover：视频遮挡区域。vpss对输出图像填充色块
- Coverex：视频遮挡区域。调用vgs对vpss通道的输出图像填充纯色块
- Overlayex：视频叠加区
- 3DNR：降噪，去除高斯噪声
- 固定角度旋转：
- 任意角度旋转
- Spread：对输入图像做展宽处理
- 鱼眼校正
- HDR 输出



# VENC：
概念：
1.PAYLOAD_TYPE_E
定义音视频净荷类型枚举。
系统采用MPEG-2将数据压缩并组装成分组，称为净荷
2.DTV系统规范 
      根据传输系统的不同，DTV系统分为三类：陆基系统 DTV-T、卫星系统 DTV-S、有线系统 DTV-C。这三类DTV系统虽然各有不同，但也有公共的特性，MPEG-2视频和音频编码系统是所有DTV系统的基础。系统采用MPEG-2将数据压缩并组装成分组，称为净荷。对净荷采用Reed-Solomon前向纠错编码，降低信号传输中引入的误码。 

3.码流（Data Rate）是指视频文件在单位时间内使用的数据流量，也叫码率，是视频编码中画面质量控制中最重要的部分。同样分辨率下，视频文件的码流越大，压缩比就越小，画面质量就越好。

4.高动态范围图像（High-Dynamic Range，简称HDR）
摘自百度百科
相比普通的图像，可以提供更多的动态范围和图像细节，根据不同的曝光时间的LDR(Low-Dynamic Range)图像，利用每个曝光时间相对应最佳细节的LDR图像来合成合成最终HDR图像 [1]  ，能够更好的反映人真实环境中的视觉效果。
如上文所说HDR，为高动态范围的简称，何为高动态范围，举例说明：
现实真正存在的亮度差，即最亮的物体亮度，和最小的物体亮度之比为  ， 而人类的眼睛所能看到的范围是  左右，但是一般的显示器，照相机能表示的只有256种不同的亮度。
但是我们可以多拍几张照片，2张，3张，....， 甚至几十张，这些照片的曝光依次增大，很多朋友应该可以想到，随着照片曝光的增大，照片会依次变亮，换一种角度，照片所表示的细节会从亮处向暗处shifting.
按照上面的理论，用很多张不同曝光的照片合成，结果图像表示的数量级一般为  甚至更多。
这样问题就出现了，2^16  甚至更高数量级的亮度只能存在电脑里，而一般的显示器只能表示256个亮度值，用256个数字来模拟2^16 个数量级所能表示的信息，这种模拟的方法就是HDR技术核心内容，学名叫Tone-Mapping（色调映射，俗名色调压缩） 。用Tone-mapping压缩以后，我们所合成的HDR影像就能很好的在显示器上显示了，能给人以震撼人心的效果。
HDR文件是一种特殊图形文件格式，它的每一个像素除了普通的RGB信息，还有该点的实际亮度信息。

5.SONSOR0_TYPE是怎么从makefile.param中读取的？
6.什么是gop
编码通道属性由三部分组成，编码器属性、码率控制器属性和帧结构类型属性，帧结构类型属性简称 GOP 类型属性。
编码器属性首先需要选择编码协议， 然后分别对各种协议对应的属性进行赋值。
编码器属性最大宽高，通道宽高必须满足如下约束：
MaxPicWidth∈[MIN_WIDTH, MAX_WIDTH]
MaxPicHeight∈[MIN_HEIGHT, MAX_HEIGHT]
PicWidth∈[MIN_WIDTH, MAX_WIDTH]
PicHeight∈[MIN_HEIGHT, MAX_HEIGHT]
最大宽高，通道宽高必须是 MIN_ALIGN 的整数倍。
其中 MIN_WIDTH， MAX_WIDTH， MIN_HEIGHT， MAX_HEIGHT，
MIN_ALIGN 分别表示编码通道支持的最小宽度，最大宽度，最小高度，最大高
度，最小对齐单元（像素）。

7.修改帧率的ffmpeg命令
也就说对于输入文件是40帧的媒体，我们可以通过ffmpeg -r 80 -i input  output、ffmpeg -r 20-i input  output使其输出文件的时长分别为原来的一半和两倍，即播放速度为原来的两倍和一半。
如果我们认为40帧的文件码流太大，我们可以通过降低输出文件帧率的方法降低码流：ffmpeg -i input  -r 20 output，这样输出文件的码流理论上为输入文件的一半左右。

