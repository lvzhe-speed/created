#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"
  

 
 

#define SPI_SPEED_2   		0
#define SPI_SPEED_4   		1
#define SPI_SPEED_8   		2
#define SPI_SPEED_16  		3
#define SPI_SPEED_32 		4
#define SPI_SPEED_64 		5
#define SPI_SPEED_128 		6
#define SPI_SPEED_256 		7


#define OLED_CS_LOW		GPIO_ResetBits(GPIOB,GPIO_Pin_5)						
#define OLED_CS_HIGH	GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define OLED_DC_LOW		GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define OLED_DC_HIGH	GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define OLED_RST_LOW	GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define OLED_RST_HIGH	GPIO_SetBits(GPIOB,GPIO_Pin_7)

void SPI1_Init();
u8 SPI1_ReadWriteByte(u8 Txdata);
void SPI1_SetSpeed(u8 SPI_SPEED);
void SPI_OLED_Init(void);
void WriteCmd(unsigned char cmd); //Ð´ÃüÁî
void WriteData(unsigned char data); //Ð´Êý¾Ý


		 
#endif

