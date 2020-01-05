#ifndef __REDRAY_H
#define __REDRAY_H

#include "stm32f10x.h"   
#include "./USART/bsp_usart.h"

extern uint8_t RedRayData,RedRayDataUpdataFlag;

void UpdataRedRayRevData(void);



#endif
