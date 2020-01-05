#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h" 
#include "stdio.h"
#include "./BUFFER/Buffer.h"

extern FIFOBufTypeDef USART2RXBuf;
extern FIFOBufTypeDef USART3RXBuf;

void USART1Init(uint32_t USART_BaudRate);//TX:PA9,RX:PA10
void USART2Init(uint32_t USART_BaudRate);//TX:PA2,RX:PA3
void USART3Init(uint32_t USART_BaudRate);//TX:PB10,RX:PB11

#endif






