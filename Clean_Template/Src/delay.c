//----------------------------------------------------------------------------------------------
// подключаем библиотеки
//----------------------------------------------------------------------------------------------
#include "delay.h"

//----------------------------------------------------------------------------------------------
// функция обработки прерывания срабатывает каждую 1ms
//----------------------------------------------------------------------------------------------
uint16_t delay_count=0;

void SysTick_Handler(void)//1ms
{
	if(delay_count > 0)												// если значение больше 0 
	{
		delay_count--;													// уменшаем на 1
	}
}

//----------------------------------------------------------------------------------------------
// Функция задержки
//----------------------------------------------------------------------------------------------
void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;									// передаём значение задержки
	
	while(delay_count){}											// Выполняем пока значение не равно 0
}

