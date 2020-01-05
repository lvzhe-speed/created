#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h" 

#define LED_ON GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define LED_OFF GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define LED_Toggle if(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))\
										GPIO_ResetBits(GPIOC, GPIO_Pin_13);\
										else GPIO_SetBits(GPIOC, GPIO_Pin_13)

void LED_GPIOInit(void);										
										
#endif
