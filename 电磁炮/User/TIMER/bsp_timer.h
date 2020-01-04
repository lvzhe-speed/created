/*
�ÿ������к���Ĭ�Ͻ���ʱ��Ƶ�ʳ�ʼ��Ϊsystemclock/72Mhz
*/
#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "stm32f10x.h"
/*
��ʼ����ʱ���жϣ�������
TIM_Period���жϼ�������
*/
void TIM1IntInit(uint16_t TIM_Period);
void TIM2IntInit(uint16_t TIM_Period);
void TIM3IntInit(uint16_t TIM_Period);
void TIM4IntInit(uint16_t TIM_Period);
/*
��ʼ����ʱ�����������������
TIM_Period��������������
TIM_Pulse���ߵ�ƽ��������
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
��ʼ����ʱ��ΪAB��������ӿڹ���
*/
void TIM1EncoderModeInit(void);//PA8/PA9
void TIM2EncoderModeInit(void);//PA0/PA1
void TIM3EncoderModeInit(void);//PA6/PA7
void TIM4EncoderModeInit(void);//PB6/PB7

#endif



