# FrameEncap
### 计算机网络实验一 

##### 编程实现IEEE802.3标准以太网封装

- 设计要求

  > 1. 编写一个简单的以太帧封装程序，要求能够模拟以太帧的封装过程。
  >
  > 要求用图形化界面，可以输入以太帧的数据字段，输出封装的帧的相关字段（前导码，帧前定界符，目的地址，源地址，帧长度，数据和校验和）l
  >
  > 1. 要求遵循IEEE802.3相关以太网协议的规定，可以封装包含标准MAC地址的以太帧。实现对以太帧的封装过程。
  >
  >    

- 程序设计流程图为

  ![CRC程序流程图](https://upload-images.jianshu.io/upload_images/4077777-98789e3da6eecf93.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



- CRC校验算法的实现

  ​	在封装以太帧的过程中，我们需要对整个帧进行CRC校验，但是校验范围不包括前导码与帧前定界符。首先，构造一个8位的寄存器CRC,并将CRC的初始值设为0。然后，将数据一次一如CRC的最低位，同时将CRC的最高位移出。当移出的数据为1时，CRC与00000111进行XOR运算；当移出的数据为0时，不做任何运算。每次CRC中的数据左移后，从输入数据中读入一位新的数据。由于左移时CRC的最低位补0，当读入的数据为1时，还需要将CRC的最低位置1.

- 用`QT`编写代码实现图形化界面

  ![Qt实现图形化界面截图](https://upload-images.jianshu.io/upload_images/4077777-cc9dfe1a03fe75e0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
  


