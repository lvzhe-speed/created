#include "RedRay.h"

uint8_t RedRayData,RedRayDataUpdataFlag=0;
const uint16_t Addr = 0x00ff;

void UpdataRedRayRevData()
{
	uint8_t ReadCount = 0,ReadData;
	while(GetFIFOBufDataSize(&USART3RXBuf))
	{
		do
		{
			if(ReadFIFOBuf(&USART3RXBuf,&ReadData,ReadCount,1))
			{
				ReadCount++;
			}
			else
			{
				return;
			}
		}while(ReadData!=Addr>>8);
		
		if(ReadFIFOBuf(&USART3RXBuf,&ReadData,ReadCount,1))
		{
			ReadCount++;
			if(ReadData==Addr&0xff)
			{
				if(ReadFIFOBuf(&USART3RXBuf,&ReadData,ReadCount,1))
				{
					RedRayData = ReadData;
					RedRayDataUpdataFlag = 1;
					DeleteFIFOBufData(&USART3RXBuf,ReadCount);
				}
				else
				{
					return;
				}
			}			
		}
		else
		{
			return;
		}
	}
}



