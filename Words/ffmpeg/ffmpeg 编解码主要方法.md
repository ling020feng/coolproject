[ffmpeg 视频录制](https://www.jianshu.com/p/0fd017336b06)

**解码：**

注册所有容器格式和CODEC:av_register_all() 	1

打开文件:av_open_input_file()

从文件中提取流信息:av_find_stream_info()	

穷举所有的流，查找其中种类为CODEC_TYPE_VIDEO	1

查找对应的解码器:avcodec_find_decoder() 	1

打开编解码器:avcodec_open()	1

为解码帧分配内存:avcodec_alloc_frame()

不停地从码流中提取出帧数据:av_read_frame()	1

判断帧的类型，对于视频帧调用:avcodec_decode_video()	1

解码完后，释放解码器:avcodec_close()	1

关闭输入文件:av_close_input_file()



**编码：**

av_register_all()：注册FFmpeg所有编解码器。	1

avformat_alloc_output_context2()：初始化输出码流的AVFormatContext。	1

avio_open()：打开输出文件。	1

av_new_stream()：创建输出码流的AVStream。

avcodec_find_encoder()：查找编码器。	1

avcodec_open2()：打开编码器。	1

avformat_write_header()：写文件头（对于某些没有文件头的封装格式，不需要此函数。比如说MPEG2TS）。1

avcodec_encode_video2()：编码一帧视频。即将AVFrame（存储YUV像素数据）编码为AVPacket（存储H.264等格式的码流数据）。1

av_write_frame()：将编码后的视频码流写入文件。	1

flush_encoder()：输入的像素数据读取完成后调用此函数。用于输出编码器中剩余的AVPacket。

av_write_trailer()：写文件尾（对于某些没有文件头的封装格式，不需要此函数。比如说MPEG2TS）1

 

**音频：**

1.av_register_all() : 注册组件, 包括FFmpeg所以编解码器
2.avformat_alloc_context(): 初始化输出码流上下文
3.avformat_open_input(): 打开输入文件,关联输出码流上下文
4.avformat_find_stream_info(): 查找读取一些音频流信息
5.avcodec_find_decoder(): 根据音频索引,找取音频解码器上下文
6.avcodec_open2(): 打开音频解码器
7.av_read_frame(): 开始解码,读取一帧数据
8.avcodec_send_packet(): 发送数据压缩包(acc/mp3格式)
9.avcodec_receive_frame(): 解码一帧采样格式(pcm格式)
10.av_samples_get_buffer_size(): 解码成功写入文件,再循环读取下一帧
11.读取帧av_read_frame() 返回值<0 则结束


























