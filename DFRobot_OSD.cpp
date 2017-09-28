#include <SPI.h>
#include <DFRobot_OSD.h>

void DFRobot_OSD::writeAddrData(unsigned char addr, unsigned char value) 
{ 
  digitalWrite(nCS , LOW); 
  SPI.transfer(addr);
  SPI.transfer(value);
  digitalWrite(nCS ,HIGH); 
}

void DFRobot_OSD::writeData(unsigned char value) 
{ 
  digitalWrite(nCS , LOW); 
  SPI.transfer(value);
  digitalWrite(nCS ,HIGH); 
}


void DFRobot_OSD::displayString(unsigned char row, unsigned char col, const char *s) 
{
  unsigned int kk;    
  unsigned char c;     
  kk = row * 30 + col;   
  writeAddrData(OSDBL,0X00);
  writeAddrData(DMAH, kk / 256);   // address
  writeAddrData(DMAL, kk % 256);   
  writeAddrData(DMM, 0x01);       // Auto Inc
  c = *s++;    
  while (c != 0){
        int i = 0;
    for(i = 0;i < 34;i++){
      if (c == tAsciiAddr[i].ascii){
        writeData(tAsciiAddr[i].addr);
      }
    }
    if ((c >= '0') && (c <='9'))
      writeData((c == '0')? 10 : c - '1' + 1);
    else if ((c >= 'A') && (c <= 'Z'))
      writeData(c - 'A' + 11);
    else if ((c >= 'a') && (c <= 'z'))
      writeData(c - 'a' + 37);

    c = *s++;
  }    
  writeData(0xff);                        // Exit Auto Inc 
  writeAddrData(VM0, 0x48); 
} 

void DFRobot_OSD::displayChar(unsigned char row, unsigned char col, unsigned char c)
{
  unsigned int kk; 
  kk = row * 30 + col; 
  writeAddrData(OSDBL,0X00);
  writeAddrData(DMAH, kk / 256); // address 
  writeAddrData(DMAL, kk % 256);
  writeAddrData(DMDI, c);
  writeAddrData(VM0, 0x48); 
}

void DFRobot_OSD::clear(void) 
{
  unsigned int i; 
  writeAddrData(DMAH, 0x00); // address 
  writeAddrData(DMAL, 0); 
  writeAddrData(DMM, 0x01); 
  for (i = 0; i < (16*30); i++) {
    writeData(0); 
  } 
  writeData(0xff); 
}

void DFRobot_OSD::AT7456EChar(unsigned char row, unsigned char col, short value) 
{ 
  unsigned short k;
  unsigned char addrH, j; 

  k = row * 30 + col; 
  addrH = k >> 8; 
  writeAddrData(OSDBL,0X00);
  writeAddrData(DMM, 0x40); 
  writeAddrData(DMAH, addrH | 0x2);
  writeAddrData(DMAL, k); 
  j = CHAR_LBC << 5; 
  if ((value >> 8) != 0)
    j |= 0x10; 
  writeAddrData(DMDI, j);
  writeAddrData(DMAH, addrH); 
  writeAddrData(DMAL, k); 
  writeAddrData(DMDI, value);
  writeAddrData(VM0, 0x48); 
}

void DFRobot_OSD::AT7456EString(unsigned char row, unsigned char col, const char *s) 
{
  unsigned short k;
  unsigned char addrH, j; 
  unsigned char c;
  unsigned short value;
  c = *s++; 
  int flag = 0;
  k = row * 30 + col; 
  writeAddrData(OSDBL,0X00);
  while (c != 0){
    flag = 0;
    int i = 0;
    for(i = 0;i < 34;i++){
      if (c == tAsciiAddr[i].ascii){
        value = tAsciiAddr[i].addr;
        flag = 1;
      }
    }
    if(flag == 0){
      if ((c >= '0') && (c <='9'))          
        value = ((c == '0')? 10 : c - '1' + 1);    
      else if ((c >= 'A') && (c <= 'Z'))      
        value = (c - 'A' + 11);      
      else if ((c >= 'a') && (c <= 'z'))        
        value = (c - 'a' + 37);      
      else
        value = (0x00);
    }
    
    addrH = k >> 8; 
    writeAddrData(DMM, 0x40); 
    writeAddrData(DMAH, addrH | 0x2); 
    writeAddrData(DMAL, k); 
    j = CHAR_LBC << 5;
    if ((value >> 8) != 0)
      j |= 0x10; 
    writeAddrData(DMDI, j); 
    writeAddrData(DMAH, addrH); 
    writeAddrData(DMAL, k); 
    writeAddrData(DMDI, value);
    c = *s++;
    k = k+1;
  }    
  writeAddrData(VM0, 0x48); 
}

void DFRobot_OSD::init()
{
  pinMode(nCS,OUTPUT);
  SPI.begin();
  writeAddrData(VM0, 0x42);              // Software Reset, takes 100us, PAL/NTSC????   
  writeAddrData(DMAH, 0x00);             // address
  writeAddrData(DMAL, 68);    
  writeAddrData(OSDM, 0x00);  
}

DFRobot_OSD::DFRobot_OSD(int CS)
{
  nCS = CS;
}

DFRobot_OSD::~DFRobot_OSD()
{

}

void DFRobot_OSD::writeAT7456E(unsigned short addr, int *dt)
{ 
  unsigned char addrH, n;
  addrH = (addr >> 8); 

  writeAddrData(VM0, (0x00));
  delay(30);
  writeAddrData(CMAH, addr);

  writeAddrData(DMM, 0);

  for (n = 0; n < 54; n++) {
    char i = *dt;
    writeAddrData(CMAL, n | (addrH << 6));
    writeAddrData(CMDI, i); 
    dt++;
  } 
  writeAddrData(CMM, RAM_NVM);  
  delay(10);

  writeAddrData(VM0, 0x01<<3);
} 

void DFRobot_OSD::changeChar(unsigned short addr,int dt[])
{
  int buf[54] = {0};
  int i = 0;
  int n = 0;
  int *p;
  for(i = 0;i < 18;i++){
    p = extend(dt[i*2]);
    buf[n++] = *p;
    buf[n++] = *(p+1);
    p = extend(dt[i*2+1]);
    buf[n++] = *p;
  } 
 writeAT7456E(addr,buf);
}

int *DFRobot_OSD::extend(int src)
{
  int i = 0;
  static int tar[2];
  tar[0] = 0;
  tar[1] = 0;
  for(i = 0;i < 4;i++){
    if((src>>i) & 0x01){
      tar[0] = 0x02 |(tar[0]<< 2);
    }
    else
      tar[0] = 0x01|(tar[0]<< 2);
  }
  for(i = 4;i < 8;i++){
    if((src>>i) & 0x01){
      tar[1] = 0x02 | (tar[1] << 2);
    }
    else
      tar[1] = 0x01| (tar[1] << 2);
  }
 
  return tar;
}
