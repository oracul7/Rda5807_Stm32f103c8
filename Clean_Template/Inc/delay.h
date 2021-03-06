#ifndef __DELAY_H
#define __DELAY_H

//----------------------------------------------------------------------------------------------
// подключаем библиотеки
//----------------------------------------------------------------------------------------------
#include "stm32f10x.h"

//----------------------------------------------------------------------------------------------
// объявляем дефайны
//----------------------------------------------------------------------------------------------
#define DELAY 1000

//----------------------------------------------------------------------------------------------
// объявляем функции данного модуля
//----------------------------------------------------------------------------------------------
void SysTick_Handler(void);
void delay_ms(uint16_t delay_temp);

#endif // __DELAY_H
