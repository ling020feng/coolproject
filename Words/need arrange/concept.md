# concept
Bootloader
时间：在嵌入式系统中，Bootloader是在操作系统内核运行之前运行的。
目的作用：
- 初始化硬件设备
- 建立内存空间映射图
- 将系统的软硬件环境带到一个合适的状态，以便为最终调用操作系统内核准备好正确的环境。

BIOS
Base Input Output System，是一组固化到计算机内主板上的一个ROM芯片上的程序，它保存着计算机最重要的基本输入输出的程序、开机后自检程序和系统自启动程序。
bootloader和BIOS区别 
Bootloader是启动引导器，起到了引导操作系统起到的目的。BIOS负责系统（主要是主板）的硬件初始化，例如CPU、内存、硬盘、键盘、显示卡、网卡等等硬件的初始化。传统的个人电脑上面的BIOS会有一个int19软件中断功能，在初始化完成后，BIOS会进入int19，寻找启动介质，如软盘，光盘，硬盘，flash或者网络等等。这里的int19就是一个bootloader，启动引导器，所以，BIOS具有Bootloader的功能。当然，bios的功能更多，比如电源管理方面的ACPI借口，USB驱动，PXE网络引导功能，硬盘加密等等。
所以，他们两个是极为想似的。bootloader应用在相对简单的系统，bios应用相对复杂的系统。

主板 bios
主板提供一系列的接合点，供处理器、显卡、生效卡、硬盘、存储器、对外设备等设备接合。它们通常直接插入有关插槽，或用线路链接。主板上最重要的构成组件是芯片组（Chipset）。而芯片组通常由北桥和南桥组成，也有些以单片机设计，增强其性能。这些芯片组为主板提供一个通用平台供不同设备连接，控制不同设备的沟通。bios是固化在主板上的一块rom芯片上的程序。

固件
固件是硬件的灵魂，其实它是一段程序，或大或小，通过这段程序，可以使得相应的硬件发挥它的功能。早期是写在rom中固化下来，现在需要提供修改升级的空间，使用eprom，eeprom和flash。

驱动
设备驱动程序，是添加到操作系统中的特殊程序，其中包含有关硬件设备的信息。此信息能够使计算机与相应的设备进行通信。

固件和驱动区别
驱动是控制被操作系统管理的外部设备的代码段，驱动会被注册到总线上，代表系统具备了驱动某种设备的能力。当设备被注册到总线的时候（一般为总线枚举发现设备），总线驱动会通过一定的策略对设备和驱动进行绑定，如果绑定成功，总线驱动会调用某个函数，把设备的信息（例如端口，中断号）传给驱动，驱动就可以对真是的物理部件进行初始化了。
固件，当驱动对设备进行初始化时，经过某种机制，可以把指定的固件加载到内存中，由驱动传输到指定的设备上。
总的来说，固件和驱动是没有什么直接关系的。就好比一个提线木偶一般，固件是木偶的完整好坏，不能缺胳膊少腿的，驱动就好比线，操作系统在上面通过线来控制木偶，木偶的胳膊腿的灵活性表明了固件的优劣，线的控制需要你知道木偶的胳膊长短这些参数，不然拉扯过度，会损坏木偶。差不多是这个意思。

HAL库
硬件抽象层是位于操作系统 内核与硬件电路之间的接口层，其目的在于将硬件抽象化。它隐藏了特定平台的硬件接口细节,为操作系统提供虚拟硬件平台,使其具有硬件无关性,可在多种平台上进行移植。 从软硬件测试的角度来看，软硬件的测试工作都可分别基于硬件抽象层来完成，使得软硬件测试工作的并行进行成为可能。


宏
计算机科学里的宏（Macro)，是一种批量处理的称谓。一般说来，宏是一种规则或模式，或称语法替换 ，用于说明某一特定输入（通常是字符串）如何根据预定义的规则转换成对应的输出（通常也是字符串)。这种替换在预编译时进行，称作宏展开。解释器或编译器在遇到宏时会自动进行这一模式替换。对于编译语言，宏展开在编译时发生，进行宏展的工具常被称为宏展开器。宏这一术语也常常被用于许多类似的环境中，它们是源自宏展开的概念，这包括键盘宏和宏语言。绝大多数情况下，“宏”这个词的使用暗示着将小命令或动作转化为一系列指令。