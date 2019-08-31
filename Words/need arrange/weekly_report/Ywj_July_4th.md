确定了实习生的任务：基于Hi3516cv500实现＂ｏｋ＂和＂6＂的识别，分两步走：

第一步是实现识别给出的内含手势的Bounding box中的手势是否为＂ｏｋ＂或＂６＂，第二步是实现返回输入帧中的手部的bvounding box


修改了宏定义，编译了修改后的ncnn，hug出现在不能调用neon加速指令机，

阅读Tensorflow Lite文档

烧写Hi3559CDMEB和Hi3519av100两块板子

