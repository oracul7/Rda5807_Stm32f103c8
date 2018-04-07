#include "ports_definition.h"

/*******************************************************************************
* Имя функции		: 	gpio_en();
* Описание			: 	настраиваем порты ввода-вывода
* Вход					: 	
* Выход					: 	
* Возвращает		: 	
* Внимание			: 	
*******************************************************************************/
void gpio_en(){
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
   
   GPIO_InitTypeDef spi_pin;
   
   //Main SPI pins 
   spi_pin.GPIO_Pin = SCK | MOSI;
   spi_pin.GPIO_Speed = GPIO_Speed_50MHz;
   spi_pin.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(PORTA, &spi_pin);
   
   //Other pins
   spi_pin.GPIO_Pin = DC | RST | CE ;
   spi_pin.GPIO_Speed = GPIO_Speed_2MHz;
   spi_pin.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(PORTA, &spi_pin);   
}
