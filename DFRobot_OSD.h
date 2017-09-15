#ifndef _OSD_H_ 
#define _OSD_H_
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
// at7456 
#define VM0 0x00 // Video Mode0 
#define VM1 0x01 // Video Mode1 
#define HOS 0x02 // Horizontal Offset 
#define VOS 0x03 // Vertical Offset 
#define DMM 0x04 // Display Memory Mode 
#define DMAH 0x05 // Display Memory Address High 
#define DMAL 0x06 // Display Memory Address Low 
#define DMDI 0x07 // Display Memory Data In 
#define CMM 0x08 // Character Memory Mode 
#define CMAH 0x09 // Character Memory Address High 
#define CMAL 0x0a // Character Memory Address Low 
#define CMDI 0x0b // Character Memory Data In
#define OSDM 0x0c // OSD Insertion Mux 
#define RB0 0x10 // Row 0 Brightness 
#define RB1 0x11 // Row 1 Brightness 
#define RB2 0x12 // Row 2 Brightness 
#define RB3 0x13 // Row 3 Brightness 
#define RB4 0x14 // Row 4 Brightness 
#define RB5 0x15 // Row 5 Brightness 
#define RB6 0x16 // Row 6 Brightness 
#define RB7 0x17 // Row 7 Brightness 
#define RB8 0x18 // Row 8 Brightness 
#define RB9 0x19 // Row 9 Brightness 
#define RB10 0x1a // Row 10 Brightness 
#define RB11 0x1b // Row 11 Brightness 
#define RB12 0x1c // Row 12 Brightness 
#define RB13 0x1d // Row 13 Brightness 
#define RB14 0x1e // Row 14 Brightness 
#define RB15 0x1f // Row 15 Brightness 
#define OSDBL 0x6c // OSD Black Level 
#define STAT 0x20 // Status 
#define DMDO 0x30 // Display Memory Data Out 
#define CMDO 0x40 // Character Memory Data Out 
#define NVM_RAM 0x50 // 将NVM中的字库读取到镜像RAM中 
#define RAM_NVM 0xa0 // 将镜像RAM中的字库数据写到NVM中 
// VM0 
#define NTSC (0 << 6) // D6 --- Vidoe Standard Select 
#define PAL (1 << 6) 
#define SYNC_AUTO (0 << 4) // D5,D4 --- Sync Select Mode 
#define SYNC_EXTERNAL (2 << 4) 
#define SYNC_INTERNAL (3 << 4) 
#define OSD_ENABLE (1 << 3) // D3 --- Enable Display of OSD image 
#define OSD_DISABLE (0 << 3) 
#define SOFT_RESET (1 << 1) // D1 --- Software Reset 
#define VOUT_ENABLE (0 << 0) 
#define VOUT_DISABLE (1 << 0)
// VM1 
#define BACKGND_0 (0 << 4) // 背景电平 WHT% 
#define BACKGND_7 (1 << 4) 
#define BACKGND_14 (2 << 4) 
#define BACKGND_21 (3 << 4) 
#define BACKGND_28 (4 << 4) 
#define BACKGND_35 (5 << 4) 
#define BACKGND_42 (6 << 4) 
#define BACKGND_49 (7 << 4) 
#define BLINK_TIME40 (0 << 2) // 闪烁周期, ms 
#define BLINK_TIME80 (1 << 2) 
#define BLINK_TIME120 (2 << 2) 
#define BLINK_TIME160 (3 << 2) // 闪烁占空比(ON : OFF) 
#define BLINK_DUTY_1_1 0 // BT : BT 
#define BLINK_DUTY_1_2 1 // BT : 2BT 
#define BLINK_DUTY_1_3 2 // BT : 3BT
#define BLINK_DUTY_3_1 3 // 3BT : BT // DMM 
#define SPI_BIT16 (0 << 6) // 写字符时采用16bit方式，字符属性来自DMM[5:3] 
#define SPI_BIT8 (1 << 6) // 写字符时用8bit方式，字符属性单独写入 
#define CHAR_LBC (1 << 5) // 本地背景 
#define CHAR_BLK (1 << 4) // 闪烁显示 
#define CHAR_INV (1 << 3) // 负像显示 
#define CLEAR_SRAM (1 << 2) // 清屏，20us 
#define VETICAL_SYNC (1 << 1) // 命令在场同步后起作用 
#define AUTO_INC (1 << 0) // 字符地址自动递增
// RBi 
#define BLACK_LEVEL_0 (0 << 2) // 0% 白电平 
#define BLACK_LEVEL_10 (1 << 2) // 10% 白电平 
#define BLACK_LEVEL_20 (2 << 2) // 20% 白电平 
#define BLACK_LEVEL_30 (3 << 2) // 30% 白电平 
#define WHITE_LEVEL_120 (0 << 0) // 120% 白电平 
#define WHITE_LEVEL_100 (1 << 0) // 110% 白电平 
#define WHITE_LEVEL_90 (2 << 0) // 90% 白电平 
#define WHITE_LEVEL_80 (3 << 0) // 80% 白电平 
// STAT 
#define PAL_DETECT (1 << 0) // 检测到PAL信号 
#define NTSC_DETECT (1 << 1) // 检测到NTSC信号 
#define LOS_DETECT (1 << 2) // 检测到LOS信号 
#define VSYNC (1 << 4) // 场同步 
/*
typedef struct 
{
	unsigned int index; // 字库索引：AT7456 = {0..255}；AT7456E = {0..511}
	unsigned char attrib; // 显示属性：D2 - LBC；D1 - BLK；D0 - INV
} CHAR_ATTRIB;
*/
typedef struct
{
  char ascii;
  short addr;
}AsciiAddr;

const AsciiAddr tAsciiAddr[]={
  {' ',0x00},        
  {'(',0x3f}, 
  {')',0x40}, 
  {'.',0x41},  
  {'?',0x42}, 
  {';',0x43}, 
  {':',0x44}, 
  {',',0x45}, 
  {'\'',0x46}, 
  {'/',0x47}, 
  {'"',0x48}, 
  {'-',0x49}, 
  {'<',0x4a}, 
  {'>',0x4b}, 
  {'@',0x4c}, 
  {'!',0x121}, 
  {'#',0x123}, 
  {'$',0x124}, 
  {'%',0x125}, 
  {'&',0x126}, 
  {'(',0x128}, 
  {')',0x129}, 
  {'*',0x12a}, 
  {'+',0x12b}, 
  {'_',0x12d}, 
  {'=',0x13d}, 
  {'[',0x15b}, 
  {']',0x15d}, 
  {'^',0x15e}, 
  {'`',0x160}, 
  {'{',0x17b}, 
  {'|',0x17c}, 
  {'}',0x17d}, 
  {'~',0x17e}, 
};


class OSD
{

public:
	OSD();
	~OSD();
	void init(int CS);
	void displayChar(unsigned char row, unsigned char col, unsigned char c); 
	void displayString(unsigned char row, unsigned char col, unsigned char *s); 
	void clear(void);
	void AT7456EChar(unsigned char row, unsigned char col, short value);
	void AT7456EString(unsigned char row, unsigned char col, unsigned char *s);
	void writeAT7456E(unsigned short addr, int *dt);
	void changeChar(unsigned short addr,int dt[]);
	
private:
	void writeAddrData(unsigned char addr, unsigned char dat); 
	void writeData(unsigned char dat); 
	int *OSD::extend(int src);
	int nCS;
};

#endif
