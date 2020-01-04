#include "buffer.h"

uint16_t GetFIFOBufDataSize(FIFOBufTypeDef* FIFOBufPtr)
{
	if(FIFOBufPtr->DataHead <= FIFOBufPtr->DataEnd)
	{
		return FIFOBufPtr->DataEnd - FIFOBufPtr->DataHead;
	}
	else
	{
		return FIFOBufPtr->BufSize + FIFOBufPtr->DataEnd - FIFOBufPtr->DataHead;
	}
}

uint8_t DeleteFIFOBufData(FIFOBufTypeDef* FIFOBufPtr,uint16_t DeleteSize)
{
	if(GetFIFOBufDataSize(FIFOBufPtr) < DeleteSize)return 0;
	else FIFOBufPtr->DataHead = (FIFOBufPtr->DataHead + DeleteSize) % FIFOBufPtr->BufSize;
	return 1;
}

void WriteFIFOBuf(FIFOBufTypeDef* FIFOBufPtr,uint8_t* WritePtr,uint16_t WriteSize)
{
	while(WriteSize--)
	{
		FIFOBufPtr->BufAddr[FIFOBufPtr->DataEnd] = *WritePtr;
		if(++FIFOBufPtr->DataEnd >= FIFOBufPtr->BufSize)
		{
			FIFOBufPtr->DataEnd = 0;
		}
		if((FIFOBufPtr->DataEnd == FIFOBufPtr->DataHead)&&
		(++FIFOBufPtr->DataHead >= FIFOBufPtr->BufSize))
		{
			FIFOBufPtr->DataHead = 0;
		}
		WritePtr++;
	}
}

uint8_t ReadFIFOBuf(FIFOBufTypeDef* FIFOBufPtr,uint8_t* ReadPtr,uint16_t OffsetAddr,uint16_t ReadSize)
{
	uint16_t DataAddr,i;
	if(GetFIFOBufDataSize(FIFOBufPtr) < OffsetAddr + ReadSize)return 0;
	for(i=0;i<ReadSize;i++)
	{
		DataAddr = (FIFOBufPtr->DataHead + OffsetAddr + i) % FIFOBufPtr->BufSize;		
		*ReadPtr = FIFOBufPtr->BufAddr[DataAddr];
		ReadPtr++;
	}
	return 1;
}



