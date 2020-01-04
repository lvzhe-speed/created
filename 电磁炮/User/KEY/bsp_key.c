#include "bsp_key.h"
#include "user_control.h"

KeyServeTypedef KeyServeStructure;
/*
按键初始化
*/
void KeyGPIOInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
}
/*
获取按键接口状态
*/
static uint8_t GetKeyInterfaceStatus()
{
	uint8_t KeyInterfaceStatus = 0;
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) KeyInterfaceStatus |= 0x01;//按键1
	else KeyInterfaceStatus &= ~0x01;
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)) KeyInterfaceStatus |= 0x02;//按键2
	else KeyInterfaceStatus &= ~0x02;
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)) KeyInterfaceStatus |= 0x04;//按键3
	else KeyInterfaceStatus &= ~0x04;
//	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15)) KeyInterfaceStatus |= 0x08;//按键4
//	else KeyInterfaceStatus &= ~0x08;
	return KeyInterfaceStatus;
}
/*
5ms周期键盘扫描函数，已消抖
*/
void Period5msKeyScan()
{
	uint8_t CurrentKeyInterfaceStatus;
	static uint16_t KeyCount;
	static uint8_t LastKeyInterfaceStatus;	
	
	CurrentKeyInterfaceStatus = GetKeyInterfaceStatus();
  
	if(CurrentKeyInterfaceStatus!=DefaultKeyInterfaceStatus)
	{
		KeyCount++;
		LastKeyInterfaceStatus = CurrentKeyInterfaceStatus;
		if(KeyCount>=KeyLongPressCount)//长按
		{
			if(KeyCount==KeyLongPressCount)
			{
				switch(LastKeyInterfaceStatus)
				{
					case 0xfe:KeyServeStructure.KeyValue = 0x11;break;
				}
			}
			KeyCount = KeyLongPressCount + 1;      
		}
	}
	else
	{
		if(KeyCount>KeyPressMINCount)
		{
			KeyServeStructure.KeyWaitServeFlag = 1;//按键等待服务标志置位
			if(KeyCount<KeyLongPressCount)//短按
			{
				switch(LastKeyInterfaceStatus)
				{
					case 0x0e-0x08:KeyServeStructure.KeyValue = 0x01;break;
					case 0x0d-0x08:KeyServeStructure.KeyValue = 0x02;break;
					case 0x0b-0x08:KeyServeStructure.KeyValue = 0x03;break;
//					case 0x07:KeyServeStructure.KeyValue = 0x04;break;
				}
			}
		}
		KeyCount = 0;       
	} 
}
/*
按键服务函数
*/
void Task1_KeyServe(float Angle)
{
	if(KeyServeStructure.KeyWaitServeFlag==1)
	{
		KeyServeStructure.KeyWaitServeFlag = 0;
		switch(KeyServeStructure.KeyValue)
		{
			case 0x01://PB12按键1
				SetElevation(Angle);
				Shoot();
				break;
			case 0x02://PB13按键2
				Charge();
				break;
			case 0x03://PB14按键3
				SetElevation(Angle);
				AotoChargeAndShoot();
				break;
//			case 0x04://PC15按键4
//				break;
		}
	}
}

void Task2_KeyServe(float Yaw,float Angle)
{
	if(KeyServeStructure.KeyWaitServeFlag==1)
	{
		KeyServeStructure.KeyWaitServeFlag = 0;
		switch(KeyServeStructure.KeyValue)
		{
			case 0x01://PB12按键1
					SetElevation(Angle);
		SetCenterDeviation(Yaw);
				Shoot();
				break;
			case 0x02://PB13按键2
				Charge();
				break;
			case 0x03://PB14按键3
					SetElevation(Angle);
		SetCenterDeviation(Yaw);
				AotoChargeAndShoot();
				break;
//			case 0x04://PC15按键4
//				break;
		}
	}
}


void Task3_KeyServe()
{
	if(KeyServeStructure.KeyWaitServeFlag==1)
	{
		KeyServeStructure.KeyWaitServeFlag = 0;
		switch(KeyServeStructure.KeyValue)
		{
			case 0x03:shoot_time=0;break;
		}
	}
}