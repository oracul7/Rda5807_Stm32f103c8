//----------------------------------------------------------------------------------------------
// подключаем библиотеки
//----------------------------------------------------------------------------------------------
#include "mcu_ini.h"

//----------------------------------------------------------------------------------------------
// Инициализируем порты ввода/вывода
//----------------------------------------------------------------------------------------------
void gpio_ini(void)
{
	
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // нужна библиотека stm32f10x_rcc.h
  GPIO_InitStructure.GPIO_Pin = LED;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(PORTC, &GPIO_InitStructure);
}
