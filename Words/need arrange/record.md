# record
SDIO：
Huawei LiteOS 提供了一套完整的 SDIO 对外接口。SDIO 扩展外设通过调用这套接口实现对其操作，包括发送命令，收发数据等。对Huawei LiteOS 的 SDIO 扩展外设开发
步骤如下：
1.包含 SDIO 对外接口必要的头文件。
#include "mmc/sdio_func.h"
此头文件声明了 SDIO 对外接口，定义了一个 struct sdio_func 用于 SDIO 外设操作SDIO 设备。
2. 调用 sdio_get_func（接口说明如表 2-1，下同）获得一个 sdio_func，后续的调用都依赖此 sdio_func。
3. 调用 sdio_en_func 使能此 sdio_func。
4. 调用 sdio_require_irq 注册 SDIO 中断，SDIO 中断会在 SDIO 驱动收到 SDIO 外设中断时触发。（此步骤根据用户需要选做）。
5. sdio_func 中有一成员 void *data，可由用户赋值使用。（此步骤根据用户需要选做）

GPIO 操作：
功能：GPIO 可配置为输入或者输出，可用于生成特定应用的输出信号或采集特定应用的输入
信号。

源码路径为 drivers/gpio，在编译脚本里指定源码路径与头文件路径，编译成功后，out/hi35xx/lib 目录下会生成名为 libgpio.a 的库文件，链接时通过-lgpio 指定对应库文件。


    HI_U32 ledFd;
    gpio_dev_init();
    if((ledFd = open("/dev/gpio",O_RDWR)) < 0)
    {
        printf("open error\n");
    }
    gpio_dev_init();
    gpio_groupbit_info group_bit_info;
    group_bit_info.groupnumber = 6;
    group_bit_info.bitnumber = 6;
    group_bit_info.value = GPIO_VALUE_HIGH;
    gpio_set_value(&group_bit_info);
    printf("gpio=%d\n",gpio_get_value(&group_bit_info));