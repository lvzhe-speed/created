#include "user_control.h"
#include "menuitem.h"
#include "CONTROL/control.h"
#include "TIMER/bsp_timer.h"
#include "oled.h"
#include "RedRay/RedRay.h"
#include "math.h"
#include "KEY/bsp_key.h"
#include "LED/bsp_led.h"
#include "stdlib.h"
#include "OPENMV/openmv.h"
#include "string.h"

#define UPER 0X78
#define DOWN 0X79
u8 Staue;//红外功能按键状态 

u8 Get_redray_uaule()
{ 
	char ch;
	switch(RedRayData)
	{
		case 0x0c:ch='1';break;
		case 0x18:ch='2';break;
		case 0x5e:ch='3';break;
		case 0x08:ch='4';break;
		case 0x1c:ch='5';break;
		case 0x5a:ch='6';break;
		case 0x42:ch='7';break;
		case 0x52:ch='8';break;
		case 0x4a:ch='9';break;
		case 0x16:ch='0';break;
		case 0x0d:ch='.';break;
		case 0x15:ch='\0';break;
		case 0x19:ch='-';break;
		case 0x09:Staue=DOWN;break;
		case 0x07:Staue=UPER;break;
		//case 0x43:ch='d';break;
		default: break;
	}
return ch;
}


//输入距离
void Mode_Task1()
{
	u8 i=0;
	char RedRay_arr[5];
	char t;//存贮单个字符
	float Angle;//角度
	float distan;
	SetElevation(0);//设置舵机俯仰角初始值为0
	SetCenterDeviation(0);//偏航角
	TIM4IntInit(5000);
	ShootAndChargeGPIOInit();
	LED_GPIOInit();
	OLED_ShowString(0,0,"enter distan",12);
	OLED_ShowString(0,24,"d vaule:_",12);
	OLED_ShowString(0,36,"pitch:",12);
	OLED_Refresh_Gram();
	while(system_run!=Stop)
	{
		if(RedRayDataUpdataFlag)//红外接受开始
		{
			RedRayDataUpdataFlag=0;
			t=Get_redray_uaule();
			if(t!='\0')
			{
				if(i==0)memset(RedRay_arr,0,sizeof(RedRay_arr));//数组清零
				OLED_ShowString(48,24,"_     ",12);//显示箭头
				OLED_Refresh_Gram();
				RedRay_arr[i]=t;
				i++;
				OLED_ShowString(48,24,(u8*)RedRay_arr,12);//显示距离
				OLED_ShowString(48+6*i,24,"_",12);
				OLED_Refresh_Gram();
			}
			else 
			{
				RedRay_arr[i]='\0';//结束此次输入
				i=0;
				distan=atof(RedRay_arr);
				OLED_ShowDecimalNumber(48,24,distan,12);
				OLED_Refresh_Gram();
				Angle=5.5189*distan*distan*distan-42.943*distan*distan+125.46*distan-112.13;
			}
			
		}
			Task1_KeyServe(Angle);
		OLED_ShowDecimalNumber(36,36,Angle,12);//显示俯仰角
		OLED_Refresh_Gram();
	}
}



//先输入偏航角，在输入距离
void Mode_Task2()
{
		u8 i=0,j=0;
	char t;//存贮单个字符
	char RedRay_arr[5];
	float Angle;//角度
	float distan;
	float yaw;//偏航角
	Staue=0;
		SetElevation(0);//设置舵机俯仰角初始值为0
	SetCenterDeviation(0);//偏航角
		ShootAndChargeGPIOInit();
	LED_GPIOInit();
		TIM4IntInit(5000);
	OLED_ShowString(0,0,"enter two values",12);
	OLED_ShowString(0,24,"yaw:_",12);
	OLED_ShowString(0,36,"d vaule:",12);
		OLED_ShowString(0,48,"pitch:",12);
	OLED_Refresh_Gram();
	while(system_run!=Stop)
	{
		if(RedRayDataUpdataFlag)
		{
			RedRayDataUpdataFlag=0;
			t=Get_redray_uaule();
			if(Staue==DOWN)j=1;
			else if(Staue==UPER)j=0;
			if(t!='\0')
			{
				if(i==0)memset(RedRay_arr,0,sizeof(RedRay_arr));//数组清零
			
				RedRay_arr[i]=t;
				i++;
				if(j==0)
				{
					OLED_ShowString(24,24,"_     ",12);//显示箭头
						OLED_Refresh_Gram();
					OLED_ShowString(24,24,(u8*)RedRay_arr,12);//显示偏航角
					OLED_ShowString(24+6*i,24,"_",12);
					OLED_Refresh_Gram();
				}else
				{
					OLED_ShowString(48,36,"_     ",12);//显示箭头
					OLED_Refresh_Gram();
					OLED_ShowString(48,36,(u8*)RedRay_arr,12);//显示距离
					OLED_ShowString(48+6*i,36,"_",12);
					OLED_Refresh_Gram();
				}
				
			}
		else //停止输入
		{
			RedRay_arr[i]='\0';
			i=0;
			if(j)
			{
				distan=atof(RedRay_arr);
				Angle=5.5189*distan*distan*distan-42.943*distan*distan+125.46*distan-112.13;
				OLED_ShowDecimalNumber(48,36,distan,12);//显示距离
				OLED_Refresh_Gram();
			}//采集距离
			else 
			{
				yaw=atof(RedRay_arr);
				OLED_ShowDecimalNumber(24,24,yaw,12);//显示偏航角
				OLED_Refresh_Gram();
			}//采集偏航角	
		}	
	}
		Task2_KeyServe(yaw,Angle);
		OLED_ShowDecimalNumber(36,48,Angle,12);//显示俯仰角
		OLED_Refresh_Gram();	
 }
}


	u8 shoot_time=0;//打炮次数
//启动OPNMV自动寻靶
void Mode_Task3()
{
	float distan;//距离
	float Angle;

		SetElevation(0);//设置舵机俯仰角初始值为0
	SetCenterDeviation(0);//偏航角
	TIM2IntInit(50000);
		TIM4IntInit(5000);//开炮定时器初始化
		ShootAndChargeGPIOInit();
	LED_GPIOInit();
	OLED_ShowString(12,0,"Homing target",12);
	OLED_ShowString(0,24,"Targe:",12);
	OLED_Refresh_Gram();
	while(system_run!=Stop)
	{
		if(TargetDistanceUpdataFlag)
		{
			if(PositionX<=80&&PositionX>=20)
		{
			if(shoot_time==0)
			{
				AotoChargeAndShoot();
				shoot_time++;
			}
		}
		TargetDistanceUpdataFlag=0;
		//distan=(-5e-17)*TargetDistance*TargetDistance*TargetDistance*TargetDistance+(1e-11)*TargetDistance*TargetDistance*TargetDistance-(8e-7)*TargetDistance*TargetDistance+0.0265*TargetDistance-326.13;
		Angle=5.5189*distan*distan*distan-42.943*distan*distan+125.46*distan-112.13;
			SetElevation(Angle);
		OLED_ShowDecimalNumber(36,24,distan,12);
			OLED_Refresh_Gram();
		}
		UpdataPositionData();
	Task3_KeyServe();
 }
}

