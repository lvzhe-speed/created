/*
该库中所有函数默认将定时器频率初始化为systemclock/72Mhz
*/
#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "stm32f10x.h"
/*
初始化定时器中断，参数：
TIM_Period：中断计数周期
*/
void TIM1IntInit(uint16_t TIM_Period);
void TIM2IntInit(uint16_t TIM_Period);
void TIM3IntInit(uint16_t TIM_Period);
void TIM4IntInit(uint16_t TIM_Period);
/*
初始化定时器方波输出，参数：
TIM_Period：方波计数周期
TIM_Pulse：高电平计数周期
*/
void Timer1OC1OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PA8
void Timer1OC2OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PA9
void Timer1OC3OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PA10
void Timer1OC4OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PA11
void Timer2OC1OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PA0
void Timer2OC2OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PA1
void Timer2OC3OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PA2
void Timer2OC4OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PA3
void Timer3OC1OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PA6
void Timer3OC2OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PA7
void Timer3OC3OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PB0
void Timer3OC4OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PB1
void Timer4OC1OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PB6
void Timer4OC2OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PB7
void Timer4OC3OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PB8
void Timer4OC4OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse);//PB9
/*
初始化定时器为AB相编码器接口功能
*/
void TIM1EncoderModeInit(void);//PA8/PA9
void TIM2EncoderModeInit(void);//PA0/PA1
void TIM3EncoderModeInit(void);//PA6/PA7
void TIM4EncoderModeInit(void);//PB6/PB7

#endif



