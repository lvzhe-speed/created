#include "bsp_timer.h"

static void TIM_OC_GPIOConfig(uint32_t RCC_APB2Periph_GPIOx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;

	GPIO_Init(GPIOx,&GPIO_InitStructure);
}

static void EncoderGPIOConfig(uint32_t RCC_APB2Periph_GPIOx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

static void TimeBaseInit(TIM_TypeDef* TIMx,uint16_t TIM_Period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TIM_Period - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;
	
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseStructure);
	
	TIM_Cmd(TIMx, ENABLE);
}

static void TimerOC1Init(TIM_TypeDef* TIMx,uint16_t TIM_Pulse)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = TIM_Pulse;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIMx, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
}

static void TimerOC2Init(TIM_TypeDef* TIMx,uint16_t TIM_Pulse)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = TIM_Pulse;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC2Init(TIMx, &TIM_OCInitStructure);
	
	TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
}

static void TimerOC3Init(TIM_TypeDef* TIMx,uint16_t TIM_Pulse)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = TIM_Pulse;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC3Init(TIMx, &TIM_OCInitStructure);
	
	TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
}

static void TimerOC4Init(TIM_TypeDef* TIMx,uint16_t TIM_Pulse)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = TIM_Pulse;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC4Init(TIMx, &TIM_OCInitStructure);
	
	TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
}

void Timer1OC1OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_8);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TimeBaseInit(TIM1,TIM_Period);
	TimerOC1Init(TIM1,TIM_Pulse);
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 
}

void Timer1OC2OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_9);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TimeBaseInit(TIM1,TIM_Period);
	TimerOC2Init(TIM1,TIM_Pulse);
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 
}

void Timer1OC3OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_10);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TimeBaseInit(TIM1,TIM_Period);
	TimerOC3Init(TIM1,TIM_Pulse);
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 
}

void Timer1OC4OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_11);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TimeBaseInit(TIM1,TIM_Period);
	TimerOC4Init(TIM1,TIM_Pulse);
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 
}

void Timer2OC1OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TimeBaseInit(TIM2,TIM_Period);
	TimerOC1Init(TIM2,TIM_Pulse);
}

void Timer2OC2OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_1);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TimeBaseInit(TIM2,TIM_Period);
	TimerOC2Init(TIM2,TIM_Pulse);
}

void Timer2OC3OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_2);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TimeBaseInit(TIM2,TIM_Period);
	TimerOC3Init(TIM2,TIM_Pulse);
}

void Timer2OC4OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_3);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TimeBaseInit(TIM2,TIM_Period);
	TimerOC4Init(TIM2,TIM_Pulse);
}

void Timer3OC1OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_6);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TimeBaseInit(TIM3,TIM_Period);
	TimerOC1Init(TIM3,TIM_Pulse);
}

void Timer3OC2OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_7);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TimeBaseInit(TIM3,TIM_Period);
	TimerOC2Init(TIM3,TIM_Pulse);
}

void Timer3OC3OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_0);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TimeBaseInit(TIM3,TIM_Period);
	TimerOC3Init(TIM3,TIM_Pulse);
}

void Timer3OC4OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_1);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TimeBaseInit(TIM3,TIM_Period);
	TimerOC4Init(TIM3,TIM_Pulse);
}

void Timer4OC1OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TimeBaseInit(TIM4,TIM_Period);
	TimerOC1Init(TIM4,TIM_Pulse);
}

void Timer4OC2OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_7);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TimeBaseInit(TIM4,TIM_Period);
	TimerOC2Init(TIM4,TIM_Pulse);
}

void Timer4OC3OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_8);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TimeBaseInit(TIM4,TIM_Period);
	TimerOC3Init(TIM4,TIM_Pulse);
}

void Timer4OC4OutputInit(uint16_t TIM_Period,uint16_t TIM_Pulse)
{
	TIM_OC_GPIOConfig(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_9);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TimeBaseInit(TIM4,TIM_Period);
	TimerOC4Init(TIM4,TIM_Pulse);
}

static void TIM_NVICConfig(uint8_t NVIC_IRQChannel,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
	
	NVIC_Init(&NVIC_InitStructure);
}

void TIM1IntInit(uint16_t TIM_Period)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TimeBaseInit(TIM1,TIM_Period);
	TIM_NVICConfig(TIM1_UP_IRQn,1,1);
	TIM_ClearFlag(TIM1,TIM_FLAG_Update);	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
}

void TIM2IntInit(uint16_t TIM_Period)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TimeBaseInit(TIM2,TIM_Period);
	TIM_NVICConfig(TIM2_IRQn,1,1);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
}

void TIM3IntInit(uint16_t TIM_Period)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TimeBaseInit(TIM3,TIM_Period);
	TIM_NVICConfig(TIM3_IRQn,1,1);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
}

void TIM4IntInit(uint16_t TIM_Period)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TimeBaseInit(TIM4,TIM_Period);
	TIM_NVICConfig(TIM4_IRQn,2,1);
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
}

void TIM1EncoderModeInit()
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	EncoderGPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_8|GPIO_Pin_9);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Falling);

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM1, 30000);

	TIM_Cmd(TIM1, ENABLE);
}

void TIM2EncoderModeInit()
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	EncoderGPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0|GPIO_Pin_1);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Falling);

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM2, 30000);

	TIM_Cmd(TIM2, ENABLE);
}

void TIM3EncoderModeInit()
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	EncoderGPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_6|GPIO_Pin_7);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Falling);

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM3, 30000);

	TIM_Cmd(TIM3, ENABLE);
}

void TIM4EncoderModeInit()
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	EncoderGPIOConfig(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6|GPIO_Pin_7);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Falling);

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM4, 30000);

	TIM_Cmd(TIM4, ENABLE);
}

//void TIM1_UP_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET) 
//	{	

//		TIM_ClearITPendingBit(TIM1,TIM_FLAG_Update);	
//	}		 	
//}

//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET) 
//	{	
//		
//		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
//	}		 	
//}

//void TIM3_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET) 
//	{	
//		
//		
//		
//		TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);	
//	}		 	
//}

//void TIM4_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET) 
//	{	

//		TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);	
//	}		 	
//}


