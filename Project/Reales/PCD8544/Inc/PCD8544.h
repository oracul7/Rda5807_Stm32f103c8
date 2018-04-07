/*******************************************************************************
* File  					:		PCD8544.h
* Description			: 	STM32F10x library for NOKIA 5110 LCD driver, PCD8544
* Author					: 	Prohorovskiy Sergey
* Note						: 	GNU General Public License, version 3 (GPL-3.0)
*******************************************************************************/
#ifndef __PCD8544_H
#define __PCD8544_H

/* Includes ********************************************************************/
#include "stm32f10x.h"

#include "ports_definition.h"
#include "PWM.h" 
#include "spi.h"

//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

/* Defines *********************************************************************/

// type of screen size

#define Height	48
#define Width		84

// PCD8544 Commandset
// ------------------
// General commands
#define POWERDOWN						0x04
#define ENTRYMODE						0x02
#define EXTENDEDINSTRUCTION				0x01
#define DISPLAYBLANK					0x00
#define DISPLAYNORMAL					0x04
#define DISPLAYALLON					0x01
#define DISPLAYINVERTED					0x05
// Normal instruction set
#define FUNCTIONSET						0x20
#define DISPLAYCONTROL					0x08
#define SETYADDR						0x40
#define SETXADDR						0x80
// Extended instruction set
#define SETTEMP							0x04
#define SETBIAS							0x10
#define SETVOP							0x80
// Display presets
#define LCD_BIAS						0x03	// Range: 0-7 (0x00-0x07)
#define LCD_TEMP						0x02	// Range: 0-3 (0x00-0x03)
#define LCD_CONTRAST					0x46	// Range: 0-127 (0x00-0x7F)

#define CHAR5x7_WIDTH				6 //5*8
#define CHAR5x7_HEIGHT				8
#define CHAR3x5_WIDTH				4 //3*5
#define CHAR3x5_HEIGHT				6

#define BuffSize						Width*Height/8

/* Enumarations ****************************************************************/
typedef enum {
	Pixel_Clear = 0,
	Pixel_Set = !Pixel_Clear
} Pixel_t;

typedef enum {
	FontSize_5x7 = 0,
	FontSize_3x5 = !FontSize_5x7
} FontSize_t;

/* Global Functions ************************************************************/
void Home(void);
void lcd_init(unsigned char contrast);
void lcd_brightness(uint16_t i);
void setContrast(unsigned char contrast);
void lcd_data(uint16_t data);
void lcd_com(uint16_t data);
void lcd_cursor(int16_t x, int16_t y);
void LCD_write_char(unsigned char c);
void LCD_write_string(char *s);


unsigned char drawNumber(long long_num);
void lcd_clear(void);
void UpdateArea(unsigned char xMin, unsigned char yMin, unsigned char xMax, unsigned char yMax);
void DrawPixel(unsigned char x, unsigned char y, Pixel_t pixel);

//--------------------------------------------------------------
#endif // __PCD8544_H
