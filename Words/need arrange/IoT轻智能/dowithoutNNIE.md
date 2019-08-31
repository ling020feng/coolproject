#### １．arm和华为的物联网解决方案比较：

---

##### arm的物联网解决方案：

Pelion 物联网平台：

- 连接管理
- 设备管理
- 数据管理

物联网设备产品

- Mbed OS
- 物联网SoC解决方案　板上有NPU智能加速引擎
- [Kigen SIM 大规模且安全的物联网连接解决方案](https://www.arm.com/products/iot/kigen-sim)

安全接入物联网的分层方案

---

##### 华为云的解决方案：

华为云平台：

- 设备连接，由华为云平台
- 设备管理，由华为云平台管理
- 数据管理，还未使用

物联网设备产品

- liteOS
- 物联网SoC解决方案　板上有NNIE和IVE智能加速引擎
- OTP安全解决方案

---

##### 二者区别：

华为提供云服务而arm未明显提及，arm有大规模的物联网安全方案而华为没有．

##### 二者相同点：

都是提供5G时代下的IoT的解决方案

arm推出了NPU芯片以及cortex-A77芯片为终端的AI部署赋能，华为也推出了自己的npu芯片

***

在两者共同认为AI能力需要下放到端侧这个大环境趋势下，我们开始考虑：端侧智能

端侧轻智能：在端侧仅有cpu和gpu的情况可以使用的快速而高效的智能算法

端侧重智能：除端侧轻智能之外，在端侧有足够算力（拥有智能加速引擎）的情况下，可以使用的算法．

#### ２．端侧轻智能:

手机端的能力有cpu,gpu,部分手机有集成npu

设备端的能力有cpu,部分有集成npu

轻智能方案不考虑npu，而只使用cpu和gpu的能力

值得注意的是手机端的gpu远不如台式机的gpu的性能，虽然有的移动端的gpu也开放了可编程接口，但是效果甚至不如单纯使用cpu．

下面是若干能够在移动端部署的深度学习的开源框架．相关信息的链接在info_link中．（大家可以对下表进行更新，可以改变结构，，添加信息，但是不要丢失信息）

| Frameworkname       | info_link                                                    |
| ------------------- | ------------------------------------------------------------ |
| CNNdroid            | [CNNdroid_github](https://github.com/ENCP/CNNdroid)                   [中文介绍](https://www.leiphone.com/news/201702/g4AJC3pUZRSgKOwx.html) |
| Baidu_Paddle-Mobile | [Paddle-mobile_github](https://github.com/PaddlePaddle/paddle-mobile) |
| PyTorch(caffe2)     | [中文手册](https://pytorch-cn.readthedocs.io/zh/latest/)     |
| Tencent_ncnn        | [NCNN使用blog](https://blog.csdn.net/u011728480/article/details/81108982?utm_source=blogxgwz1)     [树莓派上使用mtcnn人脸及特性点](http://itindex.net/detail/59256-mtcnn-%E7%89%B9%E5%BE%81-%E6%A0%91%E8%8E%93%E6%B4%BE)       [ncnn_github](https://github.com/Tencent/ncnn) |
| TensorFlow Lite     | [for Mobile & IoT主页](https://tensorflow.google.cn/lite/)   |
| Amazon_MXNet        | [MXNet is portable and lightweight, scaling effectively to multiple GPUs and multiple machines](https://github.com/apache/incubator-mxnet) |
| Microsoft_CNTK      | [Microsoft_CNTK_github](https://github.com/Microsoft/CNTK)   |

一些例子：

Caffe Android Library.
https://github.com/sh1r0/caffe-android-lib  . Accessed 2016-08-01.

Torch-7 for Android.
https://github.com/soumith/torch-android  . Accessed 2016-08-01.

A convolutional neural network for the Android
phone. https://github.com/radiodee1/  
awesome-cnn-android-python. Accessed 2016-08-01.

Facial attractiveness prediction on Android. https://github.com/eldog/fmobile  . Accessed 2016-08-01.