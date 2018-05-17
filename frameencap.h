#ifndef FRAMEENCAP_H
#define FRAMEENCAP_H
#include<iostream>
#include<string>
using namespace std;

/*
    填充以太帧的各字段:
        我们需要分别填充以太帧的各字段。前导码字段填充为七个连续的0xaa;
        帧前定界符字段填充为一个0xab;源地址与目的地址字段分别填充为MAC
        地址80-00-fe-85-3a-5f与80-00-ff-60-2c-dc。这里，我们需要
        重点考虑如何填充帧长度与数据。帧长度字段需要根据数据部分通过计算得到，
        如果数据部分长度小于46字节，需要填充0来补充46字节，这时帧长度字段可以
        填充为64,如果数据部分长度大于1500字节，需要将数据封装为多个满足要求的帧，
        这时每个帧长度需要分别进行计算。
*/
typedef struct FRAME_STRUCT
{
    unsigned char Preamble[7];  // 前导码
    unsigned char Delimiter;    // 帧前定界符
    unsigned char Destination[6];   // 目的地址
    unsigned char Source[6];    //  源地址
    unsigned short Length;  // 长度字段
    string Data;           // 数据字段(长度可变)
    unsigned int Checksum;  // 校验字段
}frame_struct;

class FrameEncap{
private:
    string SouceData;
    string DataBuf;
    frame_struct Frame;
public:
    FrameEncap();
    void SetData(string data);
    unsigned char CheckSum();
    string ShowAll();
    string enCode(unsigned char data);
    string getPreamble();
    string getDelimiter();
    string getDestination();
    string getSource();
    int getLength();
    string getData();
    unsigned int getCheckNum();
};
#endif // FRAMEENCAP_H
