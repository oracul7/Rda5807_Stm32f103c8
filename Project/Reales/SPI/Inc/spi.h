/*******************************************************************************
* File  					:		SPI.h
* Description			: 	STM32F10x library for NOKIA 5110 LCD driver, SPI
* Author					: 	Prohorovskiy Sergey
* Note						: 	GNU General Public License, version 3 (GPL-3.0)
*******************************************************************************/
#ifndef __SPI_H
#define __SPI_H

/* Includes ********************************************************************/
#include "stm32f10x_spi.h"
#include "ports_definition.h"

/* Global Functions ************************************************************/
void spi_en(void);
void spi_send(uint16_t data);
void chk_spi(void);
//--------------------------------------------------------------
#endif // __SPI_H
