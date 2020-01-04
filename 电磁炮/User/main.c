#include "stm32f10x.h"   
#include "delay.h"
#include "menuitem.h"
#include "exti.h"
#include "oled.h"
#include "./CONTROL/control.h"
#include "./TIMER/bsp_timer.h"




int main(void)
 {
	 delay_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断优先级分组
	 USART3Init(9600);
	 USART2Init(115200);
	 	Timer3OC3OutputInit(20000,1450);//PB0
	Timer3OC4OutputInit(20000,1450);//PB1
	 EXTIX_Init();//按键外部中断
	 OLED_Init();//显示模块初始化
	 Menuitem_Init();
	 Menu_OLED();
	 operate();//界面运行
	 
 }

