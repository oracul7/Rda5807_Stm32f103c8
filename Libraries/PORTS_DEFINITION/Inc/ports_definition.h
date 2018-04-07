/*******************************************************************************
* File  					:		PORTS_DEFINITION.h
* Description			: 	STM32F10x library for NOKIA 5110 LCD driver, PORTS DEFINITION
* Author					: 	Prohorovskiy Sergey
* Note						: 	GNU General Public License, version 3 (GPL-3.0)
*******************************************************************************/
#ifndef __PORTS_DEFINITION_H
#define __PORTS_DEFINITION_H

/* Includes ********************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

/* Defines *********************************************************************/
#define PORTA GPIOA

#define RST		GPIO_Pin_4	//PA4 RST
#define CE		GPIO_Pin_2	//PA2 CE
#define DC		GPIO_Pin_3	//PA3 DC
#define MOSI	GPIO_Pin_7	//PA7 Din/MOSI
#define SCK		GPIO_Pin_5	//PA5 SCK

#define BL		GPIO_Pin_1	//PA1 BL

/* Macros **********************************************************************/
#define resetOn		GPIOA->BSRR	= GPIO_BSRR_BS4      //подаём 1 на вывод RST
#define resetOff	GPIOA->BSRR	= GPIO_BSRR_BR4      //подаём 0 на вывод RST

#define ceOn			GPIOA->BSRR	= GPIO_BSRR_BS2      //подаём 1 на вывод CE
#define ceOff			GPIOA->BSRR	= GPIO_BSRR_BR2      //подаём 0 на вывод CE

#define dcOn			GPIOA->BSRR	= GPIO_BSRR_BS3      //подаём 1 на вывод CE
#define dcOff			GPIOA->BSRR	= GPIO_BSRR_BR3      //подаём 0 на вывод CE

#define blOn			GPIOA->BSRR	= GPIO_BSRR_BS1      //подаём 1 на вывод CE
#define blOff			GPIOA->BSRR	= GPIO_BSRR_BR1      //подаём 0 на вывод CE

/* Global Functions ************************************************************/
void gpio_en(void);

//--------------------------------------------------------------
#endif // __PORTS_DEFINITION_H
