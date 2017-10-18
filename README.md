# OSD Library for Arduino
This is a Library for OSD,the function is the superposition of characters

![SVG1](https://raw.githubusercontent.com/DFRobot/binaryfiles/master/DFR0515/DFR0515svg1.png)

## Table of Contents

* [Summary](#summary)
* [Methods](#methods)
* [EEPROM](#eeprom)
* [Compatibility](#compatibility)
* [History](#history)
* [Tool](#tool)
* [Credits](#credits)


<snippet>
<content>

## Summary
This is a Library for OSD,the function is the superposition of characters.And You can display certain characters on screen.

## Methods

```C++

#include <DFRobot_OSD.h>
/*
 * @brief The constructor
 *
 * @param CS Selection pin
 */
DFRobot_OSD(int CS);

/*
 * @brief Init OSD
 */
void init();

/*
 * @brief Clear screen
 */
void clear(void);

/*
 * @brief display char
 *
 * @param row Horizontal coordinate, range(0,15)
 * @param col Vertical coordinate, range(0,29)
 * @param value addr of char in eeprom
 */
void displayChar(unsigned char row, unsigned char col, unsigned short addr);

/*
 * @brief display string
 *
 * @param row Horizontal coordinate, range(0,15)
 * @param col Vertical coordinate, range(0,29)
 * @param s String
 */
void displayString(unsigned char row, unsigned char col, unsigned char *s); 

/*
 * @brief display string
 *
 * @param row Horizontal coordinate, range(0,15)
 * @param col Vertical coordinate, range(0,29)
 * @param s String
 */
void displayString(unsigned char row, unsigned char col, String s); 

/*
 * @brief Write the custom character to the OSD, replacing the original character
 *
 * @param addr Address of the stored character
 * @param dt Array generated through the tool
 */
void storeChar(unsigned short addr,int dt[]);

```

## EEPROM
page 1:  <br>
![image](https://github.com/DFRobot/DFRobot_OSD/blob/master/image/eeprom1.png)

page 2:  <br>
![image](https://github.com/DFRobot/DFRobot_OSD/blob/master/image/eeprom2.png)


## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-Board328P |      √       |             |            | 
FireBeetle-ESP32 |      √       |             |            | 
FireBeetle-ESP8266 |      √       |             |            | 
Leonardo |      √       |             |            | 

## History

- data 2017-9-27
- version V1.0


## Tool
### Custom Chinese characters
* congfig <br>
![image](https://github.com/DFRobot/DFRobot_OSD/blob/master/image/config.png)

* output <br>
![image](https://github.com/DFRobot/DFRobot_OSD/blob/master/image/putout.png)

## Credits

- author [Luyuhao  <yuhao.lu@dfrobot.com>]
