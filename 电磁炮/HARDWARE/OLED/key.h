#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
 	 
 
#define ENTER   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define UPER  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
#define DOWN  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define BACK GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)

#define ENTER_PRES	1		
#define UPER_PRES	2		 
#define DOWN_PRES	3		  
#define BACK_PRES 4

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数		

#endif
