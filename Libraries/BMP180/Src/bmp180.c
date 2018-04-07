#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"

#include "bmp180.h"
#include "delay.h"
#include "PCD8544.h"
#include "i2c.h"
//#include <math.h>

	//Read compensation registers
	 int16_t AC1 = 0, AC2 = 0, AC3 = 0; 
	 uint16_t AC4 = 0, AC5 = 0, AC6 = 0;
	 int16_t B1 = 0, B2 = 0, MB = 0, MC = 0, MD = 0;
	 
void compensation(void){

	AC1 = i2c_read(0xAA)*256 + i2c_read(0xAB);
	AC2 = i2c_read(0xAC)*256 + i2c_read(0xAD);
	AC3 = i2c_read(0xAE)*256 + i2c_read(0xAF);
	AC4 = i2c_read(0xB0)*256 + i2c_read(0xB1);
	AC5 = i2c_read(0xB2)*256 + i2c_read(0xB3);
	AC6 = i2c_read(0xB4)*256 + i2c_read(0xB5);
	 B1 = i2c_read(0xB6)*256 + i2c_read(0xB7);
	 B2 = i2c_read(0xB8)*256 + i2c_read(0xB9);
	 //MB = i2c_read(0xBA)*256 + i2c_read(0xBB);
	 MC = i2c_read(0xBC)*256 + i2c_read(0xBD);
	 MD = i2c_read(0xBE)*256 + i2c_read(0xBF);	
}

void pokaz(void) {

	//Start temperature measurement
	i2c_write(BMP180_SEND7BIT, BMP180_DEVICE_ADDRESS, BMP180_TEMPERATURA);
	
	//Wait to measurement
	//for(volatile uint32_t del = 0; del<10000; del++);
	Delay_us(4500);
	//Read uncompensated temperature value
	//uint32_t UT = i2c_read(0xF6)*256 + i2c_read(0xF7);
	uint32_t UT = i2c_read(0xF6)*256 + i2c_read(0xF7);
	
	//Start pressure measurement
  //	I2C_write(0x34, BMP180_DEVICE_ADDRESS);
	i2c_write(BMP180_SEND7BIT, BMP180_DEVICE_ADDRESS, BMP180_PRESSURE);
	
	//Wait to measurement
	Delay_us(4500);
	//for(volatile uint32_t del = 0; del<10000; del++);
	//Read uncompensated pressure value
	uint32_t UP = i2c_read(0xF6)*256 + i2c_read(0xF7);
	
	//temparature compensation
	int32_t X1 = (UT - AC6) * AC5 / 32768;
	int16_t X2 = MC * 2048 / (X1 + MD);
	int16_t B5 = X1 + X2;
  int16_t T = (B5 + 8) / 16;
	//return T;
  int cc = T * 0.1;
	int d = T - cc*10;
 
	//pressure compensation
	int16_t B6 = B5 - 4000;
	int16_t B3 = ((AC1 * 4 + (B2 * B6 / 4096 + AC2)*B6 / 2048) + 2) * 0.25;
	X1 = (AC3 + 2 * B1* B6)* B6 / 8192 / 65536 + 2;
	uint16_t B4 = AC4*(unsigned long)(X1 * 0.25 + 32768) / 32768;
	uint32_t B7 = ((unsigned long)UP - B3) * 50000;
	int32_t P = (B7 < 0x8000000 ? B7*2 / B4 : B7 / B4 * 2);
	P = P + ((3038 * (P / 256)*(P / 256) - 7357 *P ) / 65536 + 3791) / 16; //получаем давления в Па
	int32_t R = P * 0.0075;  //получаем давления в мм.р.ст.
	int dd = (P * 0.0075-R)*10; //получаем десятую долю давления в мм.р.ст.
	//int32_t Altitude = (float)44330 * (1 - pow(((float) P / 101325), 0.190295)); //получаем высоту в м над уровнем моря
	//LCD_write_char(' ');
	drawNumber(cc);
	LCD_write_char('.');
	drawNumber(d);
	LCD_write_string("             ");
	drawNumber(P);
	LCD_write_string("            ");
	drawNumber(R);
	LCD_write_char('.');
	drawNumber(dd);
	LCD_write_string("            ");
	//drawNumber(Altitude);
	//LCD_write_string("               ");
	
}
