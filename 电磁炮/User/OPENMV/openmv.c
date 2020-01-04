#include "openmv.h"

int PositionX;
uint8_t PositionXUpdataFlag=0;
uint32_t TargetDistanceBuf[10];
uint32_t TargetDistance=0;
uint8_t TargetDistanceUpdataFlag=0;
/*
函数名：GetTargetPosition
函数功能：获取目标靶与摄像头的相对位置(含限幅滤波)
入口参数：
	PositionPtr：数据接收指针，用于接收位置数据
返回值：
	接收成功：返回1
	接收失败：返回0
*/
static uint8_t GetTargetPosition(PositionTypedef* PositionPtr)
{
	int PositionX=0,PositionS=0,DataDeviation;//各个数据接收变量，数据偏差量，用于滤波
	uint8_t ReadData;//缓冲区数据接收变量，数据负值标志
	uint16_t ReadCount=0;//缓冲区读数据计数
	static int LastPositionX=0,LastPositionS=0;
	static uint8_t i,j;//滤波相关变量
//	printf("1\n");
	do
	{
		if(ReadFIFOBuf(&USART2RXBuf,&ReadData,ReadCount,1))
		{
			ReadCount++;
		}
		else//数据接收缓冲区为空
		{
//			printf("2\n");
			return 0;
		}
	}while(ReadData != 'X');
	while(ReadData != 'S')//数据帧中X位置数据末为S数据
	{
		if(ReadFIFOBuf(&USART2RXBuf,&ReadData,ReadCount,1))//从缓冲区中读取一个数据
		{
			if((ReadData>='0')&&(ReadData<='9'))//读到数字，更新数据
			{
				PositionX = 10 * PositionX + ReadData - '0';
			}
			ReadCount++;
		}
		else//缓冲区为空
		{
//			printf("3\n");
			return 0;
		}
	}
	while(ReadData != '\n')//数据帧中S位置数据末为帧结束符\n
	{
		if(ReadFIFOBuf(&USART2RXBuf,&ReadData,ReadCount,1))
		{
			if((ReadData>='0')&&(ReadData<='9'))
			{
				PositionS = 10 * PositionS + ReadData - '0';
			}
			ReadCount++;
		}
		else
		{
//			printf("6\n");
			return 0;
		}
	}
	
	DeleteFIFOBufData(&USART2RXBuf,ReadCount-1);//移除已经接收的数据
	
	DataDeviation = PositionX - LastPositionX;//依次进行限幅滤波
	if(((DataDeviation>50)||(DataDeviation<-50))&&(i<1))
	{
		i++;
//		printf("4\n");
		return 0;
	}
	else
	{
		i = 0;
	}
	DataDeviation = PositionS - LastPositionS;
	if(((DataDeviation>5000)||(DataDeviation<-5000))&&(j<1))
	{
		j++;
//		printf("5\n");
		return 0;
	}
	else
	{
		j = 0;
	}
	
//	DeleteFIFOBufData(&USART2RXBuf,ReadCount-1);//移除已经接收的数据
	LastPositionX = PositionX;
	LastPositionS = PositionS;
	PositionPtr->CurrentPositionX = PositionX;//获取目标物体与摄像头视野中心的水平偏差
	PositionPtr->CurrentPositionS = PositionS;//获取目标物体与镜头的距离
	return 1;
}
/*
更新位置数据，包括距离和水平
*/
void UpdataPositionData()
{
	PositionTypedef Position;
	uint8_t j,k;
	static uint8_t i=0;
	
	if(GetTargetPosition(&Position))
	{
		TargetDistanceBuf[i] = Position.CurrentPositionS;
		
		PositionX = Position.CurrentPositionX;//获取水平偏移
		PositionXUpdataFlag = 1;
		
		i++;
		if(i>=10)
		{
			i = 0;
			
			for(j=0;j<10;j++)//冒泡法从小到大排序
			for(k=j+1;k<10;k++)
			{
				if(TargetDistanceBuf[j]>TargetDistanceBuf[k])
				{
					TargetDistanceBuf[j] += TargetDistanceBuf[k];
					TargetDistanceBuf[k] = TargetDistanceBuf[j] - TargetDistanceBuf[k];
					TargetDistanceBuf[j] -= TargetDistanceBuf[k];
				}
			}
			TargetDistance = 0;
			for(j=1;j<9;j++)//去掉最值取平均
			{
				TargetDistance += 0.125*(float)TargetDistanceBuf[j];
			}
			TargetDistanceUpdataFlag = 1;
		}
	}
}
/*
获取水平位置数据
*/
int GetPositionXData()
{
	return PositionX;
}
/*
获取距离数据
*/
uint32_t GetDistanceData()
{
	return TargetDistance;
}
