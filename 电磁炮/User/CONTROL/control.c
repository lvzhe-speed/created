#include "control.h"

uint8_t ShootFlag=0,ChargeFlag=0,AotoChargeAndShootFlag=0;
/*
������̨��ˮƽ�����ߵ�ƫ��
*/
void SetCenterDeviation(float DeviationAngle)
{
	uint16_t TempDeviationAngle = (uint16_t)(CenterTimValue + DeviationAngle * (LevelMotorScale/90.0));
	if(TempDeviationAngle>MAXCenterDeviation)
	{
		TempDeviationAngle = MAXCenterDeviation;
	}
	else if(TempDeviationAngle<MINCenterDeviation)
	{
		TempDeviationAngle = MINCenterDeviation;
	}
	TIM_SetCompare3(TIM3, TempDeviationAngle);
}
/*
�ı���̨��ˮƽ�����ߵ�ƫ��
*/
void ChangeCenterDeviation(float ChangeAngle)
{
	uint16_t TempAngle = (uint16_t)(TIM3->CCR3 + ChangeAngle * (LevelMotorScale/90.0));
	if(TempAngle>MAXCenterDeviation)
	{
		TempAngle = MAXCenterDeviation;
	}
	else if(TempAngle<MINCenterDeviation)
	{
		TempAngle = MINCenterDeviation;
	}
	TIM_SetCompare3(TIM3, TempAngle);
}
/*
��ȡ��ǰ�趨����̨��ˮƽ�����ߵ�ƫ��
*/
float GetCenterDeviation()
{
	return (TIM3->CCR3 - CenterTimValue)*90.0/LevelMotorScale;
}
/*
������̨����
*/
void SetElevation(float Angle)
{
	uint16_t TempAngle = (uint16_t)(LevelTimValue - Angle * (ElevationMotorScale/90.0));
	if(TempAngle<Elevation45Angle)//���Ǵ���45ʱ������Ϊ45
	{
		TempAngle = Elevation45Angle;
	}
	else if(TempAngle>LevelTimValue)//����С��0ʱ������Ϊ0
	{
		TempAngle = LevelTimValue;
	}
	TIM_SetCompare4(TIM3, TempAngle);
}
/*
�ı���̨����
*/
void ChangeElevation(float ChangeAngle)
{
//	uint16_t TempAngle = (uint16_t)(TIM3->CCR4 + ChangeAngle * (ElevationMotorScale/90.0));
	uint16_t TempAngle = (uint16_t)(TIM3->CCR4 - ChangeAngle * (ElevationMotorScale/90.0));
	if(TempAngle<Elevation45Angle)//���Ǵ���45ʱ������Ϊ45
	{
		TempAngle = Elevation45Angle;
	}
	else if(TempAngle>LevelTimValue)//����С��0ʱ������Ϊ0
	{
		TempAngle = LevelTimValue;
	}
	TIM_SetCompare4(TIM3, TempAngle);
}
/*
��ȡ��ǰ�趨����̨����
*/
float GetElevation()
{
	return (LevelTimValue - TIM3->CCR4)*90.0/ElevationMotorScale;
//	return (TIM3->CCR4 - LevelTimValue)*90.0/ElevationMotorScale;
}
/*
���ƶ��ˮƽת��,ʹĿ�꿿����Ұˮƽ������
*/
void TrackTarget()
{
//	PositionTypedef Position;
	int PositionDeviation;
	
//	if(GetTargetPosition(&Position))//�ֶ�ʽ��������
//	{
		PositionDeviation = GetPositionXData() - OpenMVCenterX;
		
		if(PositionDeviation>0)
		{
			if(PositionDeviation>20)
			{
				ChangeCenterDeviation(-50*UnitAngle);
			}
			else if(PositionDeviation>10)
			{
				ChangeCenterDeviation(-15*UnitAngle);
			}
			else
			{
				ChangeCenterDeviation(-1.5*UnitAngle);
			}
		}
		else if(PositionDeviation<0)
		{
			if(PositionDeviation<-20)
			{
				ChangeCenterDeviation(50*UnitAngle);
			}
			else if(PositionDeviation<-5)
			{
				ChangeCenterDeviation(15*UnitAngle);
			}
			else
			{
				ChangeCenterDeviation(1.5*UnitAngle);
			}
		}
//	}
//	else
//	{
//		return;
//	}
}
/*
���䣬�����ƿڣ�PA0,PA1����ʼ��
*/
void ShootAndChargeGPIOInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//PA0���壨���䣩��PA1��ת����磩

	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}
/*
������ƺ����������־λ��1����TIM4�жϺ������Ʋ�������ʱ��20ms�͵�ƽ��
*/
void Shoot()
{
	ShootFlag = 1;
}
/*
�����ƺ���������־λ��1����TIM4�жϺ������Ʋ������ʱ��PA1�ߵ�ƽʱ��磩
*/
void Charge()
{
	ChargeFlag = 1;
}

void AotoChargeAndShoot()
{
	AotoChargeAndShootFlag = 1;
}

