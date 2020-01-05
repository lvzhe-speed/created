#include "control.h"

uint8_t ShootFlag=0,ChargeFlag=0,AotoChargeAndShootFlag=0;
/*
设置炮台与水平中轴线的偏角
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
改变炮台与水平中轴线的偏角
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
获取当前设定的炮台与水平中轴线的偏角
*/
float GetCenterDeviation()
{
	return (TIM3->CCR3 - CenterTimValue)*90.0/LevelMotorScale;
}
/*
设置炮台仰角
*/
void SetElevation(float Angle)
{
	uint16_t TempAngle = (uint16_t)(LevelTimValue - Angle * (ElevationMotorScale/90.0));
	if(TempAngle<Elevation45Angle)//仰角大于45时限制其为45
	{
		TempAngle = Elevation45Angle;
	}
	else if(TempAngle>LevelTimValue)//仰角小于0时限制其为0
	{
		TempAngle = LevelTimValue;
	}
	TIM_SetCompare4(TIM3, TempAngle);
}
/*
改变炮台仰角
*/
void ChangeElevation(float ChangeAngle)
{
//	uint16_t TempAngle = (uint16_t)(TIM3->CCR4 + ChangeAngle * (ElevationMotorScale/90.0));
	uint16_t TempAngle = (uint16_t)(TIM3->CCR4 - ChangeAngle * (ElevationMotorScale/90.0));
	if(TempAngle<Elevation45Angle)//仰角大于45时限制其为45
	{
		TempAngle = Elevation45Angle;
	}
	else if(TempAngle>LevelTimValue)//仰角小于0时限制其为0
	{
		TempAngle = LevelTimValue;
	}
	TIM_SetCompare4(TIM3, TempAngle);
}
/*
获取当前设定的炮台仰角
*/
float GetElevation()
{
	return (LevelTimValue - TIM3->CCR4)*90.0/ElevationMotorScale;
//	return (TIM3->CCR4 - LevelTimValue)*90.0/ElevationMotorScale;
}
/*
控制舵机水平转动,使目标靠近视野水平中轴线
*/
void TrackTarget()
{
//	PositionTypedef Position;
	int PositionDeviation;
	
//	if(GetTargetPosition(&Position))//分段式比例控制
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
发射，充电控制口（PA0,PA1）初始化
*/
void ShootAndChargeGPIOInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//PA0脉冲（发射），PA1翻转（充电）

	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}
/*
发射控制函数，发射标志位置1，由TIM4中断函数控制产生发射时序（20ms低电平）
*/
void Shoot()
{
	ShootFlag = 1;
}
/*
充电控制函数，充电标志位置1，由TIM4中断函数控制产生充电时序（PA1高电平时充电）
*/
void Charge()
{
	ChargeFlag = 1;
}

void AotoChargeAndShoot()
{
	AotoChargeAndShootFlag = 1;
}

