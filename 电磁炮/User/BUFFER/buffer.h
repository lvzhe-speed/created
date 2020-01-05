#ifndef __BUFFER_H
#define __BUFFER_H

#include "stm32f10x.h" 

typedef struct FIFOBufType
{
	uint16_t DataHead;
	uint16_t DataEnd;
	uint16_t const BufSize;
	uint8_t* const BufAddr;
}FIFOBufTypeDef;

uint16_t GetFIFOBufDataSize(FIFOBufTypeDef* FIFOBufPtr);
uint8_t DeleteFIFOBufData(FIFOBufTypeDef* FIFOBufPtr,uint16_t DeleteSize);
void WriteFIFOBuf(FIFOBufTypeDef* FIFOBufPtr,uint8_t* WritePtr,uint16_t WriteSize);
uint8_t ReadFIFOBuf(FIFOBufTypeDef* FIFOBufPtr,uint8_t* ReadPtr,uint16_t OffsetAddr,uint16_t ReadSize);

#endif


