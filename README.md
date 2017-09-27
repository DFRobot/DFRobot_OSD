# OSD Library for Arduino
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

#include <DFRobot_OSD.h>
/*
 * @brief Select the selection pin
 *
 * @param CS is the selection pin
 */
void init(int CS);

/*
 * @brief Clear the characters on the screen
 */
void clear(void);

/*
 * @brief display char of AT7456E's first page EEPROM library
 *
 * @param Row is the horizontal coordinate of the character, range(0,15)
 *
 * @param col is the vertical coordinate of the character, range(0,29)
 *
 * @param c is address of char
 */
void displayChar(unsigned char row, unsigned char col, unsigned char c);

/*
 * @brief display string,This string is composed of the character of the first page EEPROM font of AT7456E
 *
 * @param row is the horizontal coordinate of the character, range(0,15)
 *
 * @param col is the vertical coordinate of the character, range(0,29)
 *
 * @param s is string
 */
void displayString(unsigned char row, unsigned char col, unsigned char *s); 

/*
 * @brief display char of AT7456E's first and second page EEPROM library
 *
 * @param row is the horizontal coordinate of the character, range(0,15)
 *
 * @param col is the vertical coordinate of the character, range(0,29)
 *
 * @param value is address of char
 */
void AT7456EChar(unsigned char row, unsigned char col, short value);

/*
 * @brief display string,This string is composed of the character of the all of character in EEPROM font of AT7456E,the speed is slower than displayString
 *
 * @param row is the horizontal coordinate of the character, range(0,15)
 *
 * @param col is the vertical coordinate of the character, range(0,29)
 *
 * @param s is string
 */
void AT7456EString(unsigned char row, unsigned char col, unsigned char *s);

/*
 * @brief Write the custom character to the OSD, replacing the original character
 *
 * @param addr is address of the stored character
 *
 * @param dt is an array generated through the tool
 */
void changeChar(unsigned short addr,int dt[]);

```
## tool(Custom Chinese characters)
* congfig <br>
![image](https://github.com/DFRobot/DFRobot_OSD/blob/master/image/config.png)

* output <br>
![image](https://github.com/DFRobot/DFRobot_OSD/blob/master/image/putout.png)

