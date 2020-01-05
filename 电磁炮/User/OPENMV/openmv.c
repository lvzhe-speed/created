#include "openmv.h"

int PositionX;
uint8_t PositionXUpdataFlag=0;
uint32_t TargetDistanceBuf[10];
uint32_t TargetDistance=0;
uint8_t TargetDistanceUpdataFlag=0;
/*
��������GetTargetPosition
�������ܣ���ȡĿ���������ͷ�����λ��(���޷��˲�)
��ڲ�����
	PositionPtr�����ݽ���ָ�룬���ڽ���λ������
����ֵ��
	���ճɹ�������1
	����ʧ�ܣ�����0
*/
static uint8_t GetTargetPosition(PositionTypedef* PositionPtr)
{
	int PositionX=0,PositionS=0,DataDeviation;//�������ݽ��ձ���������ƫ�����������˲�
	uint8_t ReadData;//���������ݽ��ձ��������ݸ�ֵ��־
	uint16_t ReadCount=0;//�����������ݼ���
	static int LastPositionX=0,LastPositionS=0;
	static uint8_t i,j;//�˲���ر���
//	printf("1\n");
	do
	{
		if(ReadFIFOBuf(&USART2RXBuf,&ReadData,ReadCount,1))
		{
			ReadCount++;
		}
		else//���ݽ��ջ�����Ϊ��
		{
//			printf("2\n");
			return 0;
		}
	}while(ReadData != 'X');
	while(ReadData != 'S')//����֡��Xλ������ĩΪS����
	{
		if(ReadFIFOBuf(&USART2RXBuf,&ReadData,ReadCount,1))//�ӻ������ж�ȡһ������
		{
			if((ReadData>='0')&&(ReadData<='9'))//�������֣���������
			{
				PositionX = 10 * PositionX + ReadData - '0';
			}
			ReadCount++;
		}
		else//������Ϊ��
		{
//			printf("3\n");
			return 0;
		}
	}
	while(ReadData != '\n')//����֡��Sλ������ĩΪ֡������\n
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
	
	DeleteFIFOBufData(&USART2RXBuf,ReadCount-1);//�Ƴ��Ѿ����յ�����
	
	DataDeviation = PositionX - LastPositionX;//���ν����޷��˲�
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
	
//	DeleteFIFOBufData(&USART2RXBuf,ReadCount-1);//�Ƴ��Ѿ����յ�����
	LastPositionX = PositionX;
	LastPositionS = PositionS;
	PositionPtr->CurrentPositionX = PositionX;//��ȡĿ������������ͷ��Ұ���ĵ�ˮƽƫ��
	PositionPtr->CurrentPositionS = PositionS;//��ȡĿ�������뾵ͷ�ľ���
	return 1;
}
/*
����λ�����ݣ����������ˮƽ
*/
void UpdataPositionData()
{
	PositionTypedef Position;
	uint8_t j,k;
	static uint8_t i=0;
	
	if(GetTargetPosition(&Position))
	{
		TargetDistanceBuf[i] = Position.CurrentPositionS;
		
		PositionX = Position.CurrentPositionX;//��ȡˮƽƫ��
		PositionXUpdataFlag = 1;
		
		i++;
		if(i>=10)
		{
			i = 0;
			
			for(j=0;j<10;j++)//ð�ݷ���С��������
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
			for(j=1;j<9;j++)//ȥ����ֵȡƽ��
			{
				TargetDistance += 0.125*(float)TargetDistanceBuf[j];
			}
			TargetDistanceUpdataFlag = 1;
		}
	}
}
/*
��ȡˮƽλ������
*/
int GetPositionXData()
{
	return PositionX;
}
/*
��ȡ��������
*/
uint32_t GetDistanceData()
{
	return TargetDistance;
}
