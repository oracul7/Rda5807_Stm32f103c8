
/* Includes ********************************************************************/
#include "spi.h"

/*******************************************************************************
* ��� �������		: 	spi_en();
* ��������			: 	����������� SPI
* ����					: 	
* �����					: 	
* ����������		: 	
* ��������			: 	
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
* ��� �������		: 	spi_send(uint16_t data);
* ��������			: 	������� ������ �� SPI
* ����					: 	data
* �����					: 	
* ����������		: 	
* ��������			: 	
*******************************************************************************/
void spi_send(uint16_t data){
   while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
   SPI_I2S_SendData(SPI1, data);
   
}

/*******************************************************************************
* ��� �������		: 	chk_spi();
* ��������			: 	��� ������������ SPI
* ����					: 	
* �����					: 	
* ����������		: 	
* ��������			: 	
*******************************************************************************/
void chk_spi(){
   while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}
