#ifndef _MENUITEM_H
#define _MENUITEM_H
#include "stm32f10x.h"

#define  HorizontalScroll 0//�û������޸�Ϊ1������������������
enum
{
	Stop=0x10,
	Run=0x20,
};
extern u8 system_run;
void Menuitem_Init();
void main_Heading();
void Sub_Heading();
void Show_Start1();
void Show_Start2();
void Show_Start3();
/**********�����Ǿ���Ĳ������������û��������***********/
void System_Star1();
void System_Star2();
void System_Star3();


/*****************************************************/
void Menu_OLED();
void operate();
void move_arrows(u8 staue);

#endif

