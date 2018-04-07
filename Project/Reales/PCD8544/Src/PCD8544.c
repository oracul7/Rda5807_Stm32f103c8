/*******************************************************************************
 * File							:	PCD8544.c
 * Description			:	STM32F10x library for NOKIA 5110 LCD driver, PCD8544
 * Datum						:	2018.02.15
 * Version					:	1.0
 * Author						:	Prohorovskiy Sergey
 * email						:	oracul746@gmail.com
 * Web							:
 * Platform					:	OPEN103C8
 * CPU							:	STM32F103C8T6
 * IDE							:	µVision Keil 5.24.2.0
 * MDK_ARM					:	5.24.1
 * Module						:	PCD8544 LCD driver for NOKIA 5110
 * Function					:	LCD Driver
 * Pin Definitions	:	
 * 						PA4 = Reset (RST Pin, NSS)
 * 						PA2 = ChipSelect (CE Pin) 
 * 						PA3 = Mode (DC Pin)
 * 						PA7 = Data (Din Pin )
 * 						PA5 = Clock (Clk Pin) 
 *						PA1 = LED (BL Pin)
********************************************************************************/

/* Includes ********************************************************************/
#include "PCD8544.h"
#include "font.h"
//#include "font6x8.h"	  // шрифт

/*******************************************************************************/

unsigned char Buffer[BuffSize];
unsigned char UpdateXmin = 0, UpdateXmax = 0, UpdateYmin = 0, UpdateYmax = 0;
unsigned char lcd8544_buff[84*6]; // буфер дисплея

/*******************************************************************************
* Имя функции		: 	Home();
* Описание			: 	устанавливаем курсор в 0, 0
* Вход					: 	
* Выход					: 	
* Возвращает		: 	
* Внимание			: 	
*******************************************************************************/
void Home() {
	spi_send(SETXADDR | 0);
	spi_send(SETYADDR | 0);
}

/*******************************************************************************
* Имя функции		: 	lcd_init(unsigned char contrast);
* Описание			: 	инициализируем дисплей
* Вход					: 	contrast
* Выход					: 	
* Возвращает		: 	
* Внимание			: 	
*******************************************************************************/
void lcd_init(unsigned char contrast){
	
	resetOff;		//Set LCD reset = 0;
	resetOn;			//LCD_RST = 1;
	
	// Go in extended mode
	spi_send(FUNCTIONSET | EXTENDEDINSTRUCTION);
//  spi_send(0x20        | 0x01);
	
	// LCD bias select
	spi_send(SETBIAS | 0x4);
//  spi_send(0x10    | 0x4);
	
	// set VOP
	if (contrast > 0x7F) {
		contrast = 0x7F;
	}
	spi_send(SETVOP | contrast);
//  spi_send(0x80   | contrast);	

	// normal mode
	spi_send(FUNCTIONSET);
//spi_send(0x20);
	
	// Set display to Normal
	spi_send(DISPLAYCONTROL | DISPLAYNORMAL);
//  spi_send(0x08			| 0x04);
	
	//Set cursor to home position
	Home();

	//Normal display
	spi_send(DISPLAYCONTROL | DISPLAYNORMAL);
//  spi_send(0x08			| 0x04);
	
	 chk_spi();
     dcOn;
}

void lcd_brightness(uint16_t i){
	TIM_SetCompare2(TIM2, i*10);
}

void setContrast(unsigned char contrast) {
	// Go in extended mode
	spi_send(FUNCTIONSET | EXTENDEDINSTRUCTION);

	// set VOP
	if (contrast > 0x7F) {
		contrast = 0x7F;
	}
	spi_send(SETVOP | contrast);

	// normal mode
	spi_send(FUNCTIONSET);
}

void lcd_data(uint16_t data){
   dcOn;
   spi_send(data);
}

void lcd_com(uint16_t data){
   dcOff;
   spi_send(data);
}

void lcd_cursor(int16_t x, int16_t y){
   if(x < 0 || x > 84 || y < 0 || y > 5) return;
   
   lcd_com(0x40 | x);
   lcd_com(0x80 | y);
   chk_spi();
}

void LCD_write_char(unsigned char c) {
   unsigned char line;
   unsigned char ch = 0;

   c = c - 32;
   dcOn;
   for (line = 0; line < 5; line++) {
		 ch = Font3x5[c][line];
		 //ch = rusfont[c];
		 spi_send(ch);

   }
   //Delay(1); // Чтобы применился последний байт необходима задержка и пустая команда
   dcOff;  // При использования HW SPI данные действия обязательны, т.к. последний бит должен быть передан при переключении D/C
   spi_send(0x00); // Пустая команда
   //Delay(1); // Задержка, чтобы команда была отработана
	 //chk_spi();
}

/*******************************************************************************
* Function Name	: 	LCD_write_string
* Description		: 	Write string to LCD at current position.
* Input					: 	s => string pointer
* Output				: 	None
* Return				: 	None
* Внимание			: 	String must be null terminated.
*******************************************************************************/
void LCD_write_string(char *s) {
   unsigned char ch;
   while (*s != '\0') {
      ch = *s;
      LCD_write_char(ch);
      s++;
   }
	 //chk_spi();
}


unsigned char drawNumber(long long_num)
{
  unsigned char char_buffer[10]="";
  unsigned char i = 0;
  unsigned char f = 0;

  if (long_num < 0)
  {
    f=1;
    LCD_write_char('-');
    long_num = -long_num;

  }
  else if (long_num == 0)
  {
    f=1;
    LCD_write_char('0');
  
		return f;
  }


  while (long_num > 0)
  {
    char_buffer[i++] = long_num % 10;
    long_num /= 10;
  }

  f=f+i;
  for(; i > 0; i--)
  {
    LCD_write_char('0'+ char_buffer[i - 1]);

  }
  return f;
}


void lcd_clear() {
   uint16_t i;
   dcOn;
   for(i = 0; i < BuffSize; i++) spi_send(0);{
   //Delay(1);
   dcOff;
   spi_send(0x00);
   }
	 //chk_spi();
}

void UpdateArea(unsigned char xMin, unsigned char yMin, unsigned char xMax, unsigned char yMax) {
	if (xMin < UpdateXmin) {
		UpdateXmin = xMin;
	}
	if (xMax > UpdateXmax) {
		UpdateXmax = xMax;
	}
	if (yMin < UpdateYmin) {
		UpdateYmin = yMin;
	}
	if (yMax > UpdateYmax) {
		UpdateYmax = yMax;
	}
}

void DrawPixel(unsigned char x, unsigned char y, Pixel_t pixel) {
	if (x >= Width) {
		return;
	}
	if (y >= Height) {
		return;
	}

	if (pixel != Pixel_Clear) {
		Buffer[x + (y / 8) * Width] |= 1 << (y % 8);
	} else {
		Buffer[x + (y / 8) * Width] &= ~(1 << (y % 8));
	}
	UpdateArea(x, y, x, y);
}
