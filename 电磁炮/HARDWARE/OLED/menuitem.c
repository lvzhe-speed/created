#include "menuitem.h"
#include "key.h"
#include "oled.h"
#include "delay.h"
#include "oled.h"
#include "user_control.h"

#define UP 0
#define DW 1

void (*oper_fuc[3])();//函数指针数组

u8 system_run;
void System_Star1()
{
	OLED_Clear();
	OLED_ShowString(12,32,"system ready!",12);
	OLED_Refresh_Gram();
	delay_ms(200);
	/***以下是我测试用的函数，用户可以在下面改写自己的***/
	OLED_Clear();
	Mode_Task1();
}

void System_Star2()
{
OLED_Clear();
	OLED_ShowString(12,32,"system ready!",12);
	OLED_Refresh_Gram();
	delay_ms(200);
	/***以下是我测试用的函数，用户可以在下面改写自己的***/
	OLED_Clear();
	Mode_Task2();
}

void System_Star3()
{
OLED_Clear();
	OLED_ShowString(12,32,"system ready!",12);
	OLED_Refresh_Gram();
	delay_ms(200);
	/***以下是我测试用的函数，用户可以在下面改写自己的***/
	OLED_Clear();
	Mode_Task3();
}
void Menuitem_Init()
{
	oper_fuc[0]=System_Star1;
	oper_fuc[1]=System_Star2;
	oper_fuc[2]=System_Star3;

}

void main_Heading()
{
OLED_ShowString(20,0,"EMP",16);//此处可随用户更改
}

void Sub_Heading()
{
OLED_ShowString(0,16,"electromagnetic gun",12);//此处可随用户更改
}

void Show_Start1()
{
	OLED_ShowString(40,28,"  Start1",12);
}

void Show_Start2()
{
	OLED_ShowString(40,40,"  Star2",12);
}

void Show_Start3()
{
	OLED_ShowString(40,52,"  Star3",12);
}


void Menu_OLED()
{
	#if HorizontalScroll
	OLED_HorizontalScroll(6,7);
	#else
	OLED_StopHorizontalScroll();
	#endif
	main_Heading();
	Sub_Heading();
	Show_Start1();
	Show_Start2();
	Show_Start3();
	OLED_Refresh_Gram();
}



int ypos;//记录光标的位置

void move_arrows(u8 staue)//移动箭头
{	
	static int y=0;
	if(staue==UP)
	{
		OLED_ShowString(40,y+28,"  ",12);
			OLED_Refresh_Gram();
		y=y-12;
		if(y<0)y=24;
		OLED_ShowString(40,y+28,"->",12);
			OLED_Refresh_Gram();
		ypos=y;
	
	}
	if(staue==DW)
	{
	OLED_ShowString(40,y+28,"  ",12);
		y=y+12;
				OLED_Refresh_Gram();
		if(y==36)y=0;
		OLED_ShowString(40,y+28,"->",12);
		ypos=y;
		OLED_Refresh_Gram();
	}
	

}



void operate()
{
	u8 key;
	u8 i=0;
	int count=0;//选中功能号
	KEY_Init();
	OLED_ShowString(40,28,"->",12);
	OLED_Refresh_Gram();
	while(1)
	{
		key=KEY_Scan(0);
		switch(key)
		{
			case DOWN_PRES:		//向下移动的按键
			{
				if(i!=0)break;
				move_arrows(DW);
				count++;
			if(count==3)//选中的功能号
			{
				count=0;
			}
		}break;
			case UPER_PRES://向上移动的按键
		{
			if(i!=0)break;//在没有返回主菜单前按键无效
			count--;
			move_arrows(UP);
			if(count<0)
			{
			count=2;
			}
		}break;
			case ENTER_PRES://确认按键
			{	
				i++;
				system_run=Run;
				oper_fuc[count]();
				
			}break;
			case BACK_PRES:
			{
			
				i=0;
					OLED_Clear();
					Menu_OLED();
					OLED_ShowString(40,ypos+28,"->",12);
					OLED_Refresh_Gram();
					break;
				

			}
		
		}
	}


}