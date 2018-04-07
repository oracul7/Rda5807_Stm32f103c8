/*******************************************************************************
* File  					:		scaner.h
* Description			: 	STM32F10x library for I2C SCANER, SCANER
* Author					: 	Prohorovskiy Sergey
* Note						: 	GNU General Public License, version 3 (GPL-3.0)
*******************************************************************************/
#ifndef __BMP180_H
#define __BMP180_H

#define BMP180_SEND7BIT					0xEF
#define BMP180_PRESSURE					0x34
#define BMP180_TEMPERATURA			0x2E
#define BMP180_DEVICE_ADDRESS		0xF4
#define I2Cx_RCC				RCC_APB1Periph_I2C1
#define I2Cx						I2C1
#define I2C_GPIO_RCC		RCC_APB2Periph_GPIOB
#define I2C_GPIO				GPIOB
#define I2C_PIN_SDA			GPIO_Pin_7
#define I2C_PIN_SCL			GPIO_Pin_6

void compensation(void);
void pokaz(void);

//--------------------------------------------------------------
#endif // __BMP180_H
