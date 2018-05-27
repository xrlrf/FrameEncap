#include "frameencap.h"
#define N 1000

FrameEncap::FrameEncap()
{
    this->init();
}

FrameEncap::FrameEncap(string data)
{
    this->init();
    this->SetData(data);
}
void FrameEncap::init()
{
    for(int i = 0; i < 7 ; i++)
        Frame.Preamble[i] = char(0xaa); // 填充前导码

    Frame.Delimiter = char(0xab);   // 填充帧前定界符

    Frame.Destination[0] = char(0x80);  // 填充目的地址
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

    if(DataLen < 46){   //待修改
        for(int i = 0 ; i < 46-DataLen; i++)
            data += char(0x00);
        this->SouceData = data;
    }else{
        if(DataLen > 1500)
        {
            this->SouceData = data.substr(0,1499);
            this->DataBuf = data.substr(1500,DataLen);
        }else{
            this->SouceData = data;
        }
    }
    Frame.Data = this->SouceData;
    int size = this->Frame.Data.length() + 18;
    if(size > 255)
    {
        this->Frame.length[0] = (char)(size%255);
        this->Frame.length[1] = (char)size;
    }else{
        this->Frame.length[0] = 0x00;
        this->Frame.length[1] = (char)size;
    }
}

unsigned char FrameEncap::CheckSum()
{
    char POLY[33] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};
    int size = this->Frame.Data.length()*8 + 14*8;
    char * addr = (char *)malloc(sizeof(char)*(size + 32));

    int k = 0;
    int i = 0;
    for(; i < 48 ; )
    {
        for(uint8_t j = 0x80 ; j > 0 ; j>>=1)
            addr[i++] = ((Frame.Destination[k] & j) != 0);
        k++;
    }
    for( k = 0 ; i < 48 + 48 ;)
    {
        for(uint8_t j= 0x80; j > 0 ; j >>= 1)
            addr[i++] = ((Frame.Source[k] & j) != 0);
        k++;
    }

    for(k = 0 ; i < 48 + 48 + 16 ; )
    {
        for(uint8_t j = 0x80 ; j > 0 ; j >>= 1)
            addr[i++] = ((Frame.length[k] & j) != 0);
        k++;
    }

    for(k = 0 ; i < size ; )
    {
        for(uint8_t j = 0x80 ; j > 0 ; j >>= 1)
            addr[i++] = ((Frame.Data[k] & j) != 0);
        k++;
    }

    for(; i < size + 32 ; i++)
        addr[i] = 0;

    char cal[33] = {0};
    for(int i = 0 ; i < 33 ; i++)
        cal[i] = addr[i];

    for(int i = 33 ; i < size + 33 ; i++)
    {
        if(cal[0] == 1)
            for(int j = 0 ; j < 32 ; j++)
                cal[j] = (cal[j+1]^POLY[j+1]);
        else
            for(int j = 0 ; j < 32 ; j++)
                cal[j] = cal[j+1];
        cal[32] = addr[i];
    }

    for(int k = 0 ; k < 4 ; k++)
    {
        unsigned char temp = 0;
        for(int i = 0 ; i < 8 ; i++)
        {
            temp <<= 1;
            temp |= cal[k*8 + i];
        }

        Frame.Checksum[k] = temp;
    }
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
string FrameEncap::getLength()
{
    string info = "";
    for(int i = 0 ; i < 2 ; i++)
    {
        info += enCode(this->Frame.length[i]);
    }
    return info;
}
string FrameEncap::getData()
{
    return this->Frame.Data;
}

string FrameEncap::getCheckNum()
{
    string info = "";
    for(int i = 0 ; i < 4 ; i++)
    {
        info += enCode(this->Frame.Checksum[i]);
    }
    return info;
}

string FrameEncap::ShowAll()
{
    string info = "";

    info += "Preamble:" + getPreamble() + "\n";
    info += "Delimiter:" + getDelimiter() + "\n";
    info += "Destination:" + getDestination() + "\n";
    info += "Source:" + getSource() + "\n";
    info += "Length:" + getLength() + "\n";
    info += "Data:" + getData() + "\n";
    info += "CheckSum:" + getCheckNum()+ "\n";
    return info;
}

string FrameEncap::enCode2(string str)
{
    char buf[N];
        string info = "";
        for(int i = 0 ; i < str.length() ; i++)
        {
            for(int j = 7; j >= 0; j--)
            {
                sprintf(buf,"%d",(str[i] & 1<<j)!=0);
                info += buf;
            }

        }
        return info;
}

unsigned int FrameEncap::GetCrc32(string InStr,unsigned int len)
{
  //生成Crc32的查询表
  unsigned int Crc32Table[256];
  int i,j;
  unsigned int Crc;
  for (i = 0; i < 256; i++){
    Crc = i;
    for (j = 0; j < 8; j++){
      if (Crc & 1)
        Crc = (Crc >> 1) ^ 0xEDB88320;
      else
        Crc >>= 1;
    }
    Crc32Table[i] = Crc;
  }

  //开始计算CRC32校验值
  Crc=0xffffffff;
  for(int i=0; i<len; i++){
    Crc = (Crc >> 8) ^ Crc32Table[(Crc & 0xFF) ^ InStr[i]];
  }

  Crc ^= 0xFFFFFFFF;

  return Crc;
}

