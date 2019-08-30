av_frame_get_buffer() 分配缓冲区

av_opt_set(c->priv_data, "preset", "superfast", 0);

avcodec_find_encoder() 发现编码器

av_dump_format() 将音频格式log输出到指定文件

avformat_open_input



avformat_new_stream

avformat_new_stream 在 AVFormatContext 中创建 Stream 通道。

AVFormatContext ：

    unsigned int nb_streams;    记录stream通道数目。
    AVStream **streams;    存储stream通道。

AVStream ：

    int index;   在AVFormatContext 中所处的通道索引








JNI函数：

GetDirectBufferAddress() :允许对象访问Java给定的同一块内存地址

NewDirectByteBuffer():生成一个Java能读写的内存

NewGlobalRef(): 创建本地应用

DeleteGlobalRef(): 释放本地的应用



   AVFormatContext，AVStream，AVCodecContext，AVPacket，AVFrame等，它们的关系解释如下：

   一个AVFormatContext包含多个AVStream，每个码流包含了AVCodec和AVCodecContext，AVPicture是AVFrame的一个子集，

他们都是数据流在编解过程中用来保存数据缓存的对像，从数据流读出的数据首先是保存在AVPacket里，也可以理解为一个AVPacket最多只包含一个AVFrame，

而一个AVFrame可能包含好几个AVPacket，AVPacket是种数据流分包的概念。

**结构体基本知识**

1）AVFormatContext   封装格式上下文结构体，也是统领全局的结构体，保存了视频文件封装格式相关信息

​        ** iformat: 输入视频的AVInputFormat*

​        ** nb_steams: 输入视频的AVSteam个数*

​        ** steams：输入视频的AVSteam[]数组*

​        ** duration: 输入视频的时长(以微秒为单位)*

​        ** bit_rate: 输入视频的码率*

2.1)AVOutputFormat 各种输出格式信息和常规设置

```
const char *long_name;//格式的描述性名称，易于阅读。
enum AVCodecID audio_codec; //默认的音频编解码器
enum AVCodecID video_codec; //默认的视频编解码器
enum AVCodecID subtitle_codec; //默认的字幕编解码器
```

2）AVInputFormat   每种封装格式（例如FLV MKV MP4 AVI）对应的一个结构体

​        ** name: 封装格式名称*

​        ** long_name: 封装格式的长名称*

​        ** extensions: 封装格式的扩展名*

​        ** id: 封装格式ID*

3）AVStream   视频文件中每个视频(音频)流对应一个该结构体

​        ** id: 序号*

​        ** codec: 该流对应的AVCodecContext*

​        ** time_base: 该流的时基(用来为视频或者音频设定播放位置的)*

4)  AVCodecContex   编码器上下文结构体，保存了视频(音频)编解码相关信息

​        ** codec: 编解码器的AVCodec*

​        ** thread_count: 线程数(编码时可以自己设置)*

​        ** width，height: 图像的宽高(只针对视频)*

​        ** pix_fmt: 像素格式(只针对视频)*

​        ** sample_rate: 采样率(只针对音频)*

​        ** channels: 声道数(只针对音频)*

​        ** sample_fmt: 采样格式(只针对音频)*

​        **codec_type：编解码器的类型（视频，音频...）*

4）AVCodec   每种视频(音频)编解码器(例如H.264解码器)对应的一个改结构体

​        **name：编解码器的名字，比较短*

​        **long_name：编解码器的名字，全称，比较长*

​        **type：指明了类型，是视频，音频，还是字幕*

​        ** id: 编解码器ID*

5）AVPacket    存储一帧压缩编码后的数据

​        ** pts: 本帧数据显示的时间，比较关键的数据，在做seek和播放进度的时候都要用到它，pts只是一个数量，对应于AVStream->time_base，要根据time_base才能转换为具体的时间,音频和视频一般有不同的time_base，所以在做音视频同步一定要做转换，不能直接拿pts做。*

​        ** dts: 基本属性等同于pts，区别就是dts对应的是解码时间不是显示时间，解码后会放入缓冲，比如h264，如果有b帧，则要先解码后面的b帧，再解码之前的帧。*

​        ** data: 压缩编码数据(h.264数据)*

​        ** size: 压缩编码数据大小*

​        ** stream_index: 帧数据所属流的索引，用来区分音频，视频，和字幕数据。*

6）AVFrame   存储一帧解码后像素(采样)数据

​         **data[AV_NUM_DATA_POINTERS]：指针数组，存放YUV数据的地方。如图所示，一般占用前3个指针，分别指向Y，U，V数据。 对于packed格式的数据（例如RGB24），会存到data[0]里面。 对于planar格式的数据（例如YUV420P），则会分开成data[0]，data[1]，data[2]…（YUV420P中data[0]存Y，data[1]存U，data[2]存V）。*

​        **linesize[AV_NUM_DATA_POINTERS]：图像各个分量数据在此结构体中的的宽度。注意这并不是图像的宽度。在此例子中图像的尺寸为672X272，而亮度分量的宽度为704，应该是图像宽度经过64对齐后的结果。*

​        ** extended_data：指向了图像数据。*

​        ** width：图像的宽。*

​        **height：图像的宽高。*

​        **nb_samples：此帧音频的点数。*

​        **format：像素类型（视频），样点类型（音频）。*