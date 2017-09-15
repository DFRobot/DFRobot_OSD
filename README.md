# AT7456E Library for Arduino
This is a Library for OSD,the function is the superposition of characters
## Table of Contents

* [Summary](#summary)
* [Methods](#methods)

<snippet>
<content>

## Summary
This is a Library for OSD,the function is the superposition of characters.And You can display certain characters on screen.

## Methods

```C++

#include <OSD.h>
//init OSD, CS is the selected pin
void init(int CS);

//Clear the characters on the screen
void clear(void);

//display char of AT7456E's first page EEPROM library
//row is range(0,15)  col is range(0,29)  c is address of char
void displayChar(unsigned char row, unsigned char col, unsigned char c);

//display string,This string is composed of the character of the first page EEPROM font of AT7456E
void displayString(unsigned char row, unsigned char col, unsigned char *s); 
    
//display char of AT7456E's first and second page EEPROM library
//value is address of char
void AT7456EChar(unsigned char row, unsigned char col, short value);

//display string,This string is composed of the character of the all of  EEPROM font of AT7456E
//the speed is slower than displayString
void AT7456EString(unsigned char row, unsigned char col, unsigned char *s);
   
//Write the custom character to the OSD, replacing the original character
//dt[] is an array generated through the tool
void changeChar(unsigned short addr,int dt[]);

```

