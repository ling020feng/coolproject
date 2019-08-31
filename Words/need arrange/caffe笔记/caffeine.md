问题１：caffe训练数据的时候用lmdb格式，那么使用的时候是否也用lmdb格式?以及 extract_feature 也是输出 lmdb 数据？

    答：caffe数据源可以来自于数据库，内存，HDF5，图片或者windowfile.txt
    　　同样的图片放在不同的位置信息是不会变的，只是对应不同的数据需要在.prototxt文件中用不同的数据层读取
    那么如何将图片数据转成lmdb数据呢？
    用convert_imageset命令，使用这个命令的时候出现了一个小插曲，该可执行文件在~/Dev/caffe/build/tools
    无法直接命令行使用，添加一下环境变量就可以用了
    
问题２：什么是lmdb格式?

    答：lighting memory mapped database．

问题３：wk文件生成的过程需要什么？或者我们该在此提供一种标准的生成wk文件的过程．

    答：仅有一个prototxt部署文件和.caffemodel能否生成.wk文件，还需要什么：
        在探索中．．．．．．
        4月11日更新：今天要完成四件事：我现在有caffemodel和prototxt文件，查看SVP开发指南，然后就要做：
                                        如何生成.wk文件，
                                        如何控制输入格式，
                                        如何控制输出格式，
                                        形成开发文档
                    阅读待转换的prototxt文件，要参考：SVP开发指南中的nnie开发指南/nnie介绍/nnie规格/层级联和层规格，
                    查看各层是否被公开支持，或者非公开支持．
                    
        SVP开发指南中的nnie开发指南/nnie介绍/nnie规格/其他特性中支持其他层上报如何实现
        
        我们要通过硬件(板子)把YUV转成RGB实现，然后传给神经网络
        
        注意一下这一点，进行网络的优化，支持高效模式完成 in-place 激活运算： 类似 Conv+ReLu 计算，使用 3.6 章节中的
        in-place 描述方案，硬件执行效率更高
        
        输出特征数据尺寸在 16*16 时，读参数的 DDR 带宽与卷积计算基本匹配
        #意味着16*16跑得最快，高于16*16会跑得慢一点，低于16*16不会跑得更快，已经到DDR的上限了
        
        deploy.prototxt文件的输入层格式用格式二，见SVP开发指南3.2.1
        
        layer {
            name: "data"
            type: "Input"
            top: "data"
            input_param { 
                shape: {
                    dim: 1
                    dim: 3
                    dim: 16
                    dim: 16 
                }
            }
        }
        
        
4月12日更新：
        
今天生成了.wk文件，准备用getresults函数查看结果
        
注意一点：windows下图片路径内容用绝对路径

4月13日更新：

.wk文件能够使用，程序中调用的参数和提取blob的过程还有错误需要修改

今天使用了minicom，明天大概就是看源码，改代码，调试的一天．

very happy，终于开始调代码了．


目前在用mnist样例学习实际操作caffe，把训练的prototxt文件放到[Netscope](http://ethereon.github.io/netscope/#/editor)作对比

有用的命令：

把图片生成lmdb文件：

写一个.sh文件，生成一个包含各图片路径信息的txt文件，执行：convert_imageset 路径/\*.txt 路径/*.lmdb

生成.binaryproto文件的命令：

sudo build/tools/compute_image_mean examples/mnist/mnist_train_lmdb examples/mnist/mean.binaryproto
