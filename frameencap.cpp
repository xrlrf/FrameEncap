#include "frameencap.h"

FrameEncap::FrameEncap()
{
    for(int i = 0; i < 7 ; i++)
        Frame.Preamble[i] = char(0xaa); // 填充前导码
    Frame.Delimiter = char(0xab);   // 填充帧前定界符
    Frame.Destination[0] = char(0xab);  // 填充目的地址
    Frame.Destination[1] = char(0x00);
    Frame.Destination[2] = char(0xff);
    Frame.Destination[3] = char(0x60);
    Frame.Destination[4] = char(0x2c);
    Frame.Destination[5] = char(0xdc);
    Frame.Source[0] = char(0x80);
    Frame.Source[1] = char(0x00);
    Frame.Source[2] = char(0xfe);
    Frame.Source[3] = char(0x85);
    Frame.Source[4] = char(0x3a);
    Frame.Source[5] = char(0x5f);
}

void FrameEncap::SetData(string data)
{
    int DataLen = data.length();
    DataBuf = data;
    if(DataLen < 46){   //待修改
        for(int i = 0 ; i < 46-DataLen; i++)
            DataBuf += char(0x00);
        this->SouceData = DataBuf;
    }else{
        if(DataLen > 1500)
        {
            this->SouceData = data.substr(0,1499);
            DataLen = DataLen - 1500;
        }else{
            this->SouceData = DataBuf;
        }
    }
    Frame.Length = this->SouceData.length()+18;
    Frame.Data = this->SouceData;
}

unsigned char FrameEncap::CheckSum()
{
    unsigned char crc = 0;
    for(int i = 0; i < 6; i++)
    {
        unsigned char temp = this->Frame.Destination[i];
        for(unsigned char j = (unsigned char)0x80; j > 0; j>>=1)
        {
            if(crc & 0x80)
            {
                crc <<= 1;
                if(temp & j)
                    crc ^= 0x01;
                crc ^= 0x07;
            }
            else
            {
                crc <<= 1;
                if(temp & j)
                    crc ^= 0x01;
            }
        }
    }

    for(int i = 0; i < 6; i++)
    {
        unsigned char temp = this->Frame.Source[i];
        for(unsigned char j = (unsigned char)0x80; j > 0; j>>=1)
        {
            if(crc & 0x80)
            {
                crc <<= 1;
                if(temp & j)
                    crc ^= 0x01;
                crc ^= 0x07;
            }
            else
            {
                crc <<= 1;
                if(temp & j)
                    crc ^= 0x01;
            }
        }
    }

    int size = this->SouceData.length();
    for(int i = 0; i < size; i++)
    {
        unsigned char temp = this->SouceData[i];
        for(unsigned char j = (unsigned char)0x80; j > 0; j>>=1)
        {
            if(crc & 0x80)
            {
                crc <<= 1;
                if(temp & j)
                    crc ^= 0x01;
                crc ^= 0x07;
            }
            else
            {
                crc <<= 1;
                if(temp & j)
                    crc ^= 0x01;
            }
        }
    }
    this->Frame.Checksum = crc;
    return crc;
}

string FrameEncap::enCode(unsigned char data)
{
    char buff[10];
    sprintf(buff,"%#x",data);
    string s = buff;
    return s;
}

string FrameEncap::getPreamble()
{
    string info = "";
    for(int i = 0 ; i < 7; i++)
    {
        info += enCode(this->Frame.Preamble[i]);
    }
    return info;
}
string FrameEncap::getDelimiter()
{
    string info = "";
    info += enCode(this->Frame.Delimiter);
    return info;
}
string FrameEncap::getDestination()
{
    string info = "";
    for(int i = 0 ; i < 6; i++)
    {
        info += enCode(this->Frame.Destination[i]);
    }
    return info;
}
string FrameEncap::getSource()
{
    string info = "";
    for(int i = 0 ; i < 6; i++)
    {
        info += enCode(this->Frame.Destination[i]);
    }
    return info;
}
int FrameEncap::getLength()
{
    return (int)this->Frame.Length;
}
string FrameEncap::getData()
{
    return this->Frame.Data;
}

unsigned int FrameEncap::getCheckNum()
{
    return this->Frame.Checksum;
}

string FrameEncap::ShowAll()
{
    string info = "";
    info += "Preamble:" + getPreamble() + "\n";
    info += "Delimiter:" + getDelimiter() + "\n";
    info += "Destination:" + getDestination() + "\n";
    info += "Source:" + getSource() + "\n";
    info += "Length:" + std::to_string(getLength()) + "\n";
    info += "Data:" + getData() + "\n";
    info += "CheckSum:" + std::to_string(getCheckNum())+ "\n";
    return info;
}
