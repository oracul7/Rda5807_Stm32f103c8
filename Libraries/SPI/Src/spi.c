
/* Includes ********************************************************************/
#include "spi.h"

/*******************************************************************************
* Имя функции		: 	spi_en();
* Описание			: 	настраиваем SPI
* Вход					: 	
* Выход					: 	
* Возвращает		: 	
* Внимание			: 	
*******************************************************************************/
void spi_en(){
   SPI_InitTypeDef spi;
   
   spi.SPI_Direction = SPI_Direction_1Line_Tx;
   spi.SPI_Mode = SPI_Mode_Master;
   spi.SPI_DataSize = SPI_DataSize_8b;
   
   spi.SPI_CPHA = SPI_CPHA_1Edge;
   spi.SPI_CPOL = SPI_CPOL_Low;
   spi.SPI_NSS = SPI_NSS_Soft;
   
   spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
   spi.SPI_FirstBit = SPI_FirstBit_MSB;
   
   SPI_Init(SPI1, &spi);
   SPI_Cmd(SPI1, ENABLE);
}

/*******************************************************************************
* Имя функции		: 	spi_send(uint16_t data);
* Описание			: 	передаём данные по SPI
* Вход					: 	data
* Выход					: 	
* Возвращает		: 	
* Внимание			: 	
*******************************************************************************/
void spi_send(uint16_t data){
   while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
   SPI_I2S_SendData(SPI1, data);
   
}

/*******************************************************************************
* Имя функции		: 	chk_spi();
* Описание			: 	ждём освобождения SPI
* Вход					: 	
* Выход					: 	
* Возвращает		: 	
* Внимание			: 	
*******************************************************************************/
void chk_spi(){
   while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}
