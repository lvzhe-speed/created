#include "bsp_usart.h"
/*
串口2接收缓冲区
*/
uint8_t USART2RXBufAddr[16];
FIFOBufTypeDef USART2RXBuf = {0,0,16,USART2RXBufAddr};

/*
串口3接收缓冲区
*/
uint8_t USART3RXBufAddr[16];
FIFOBufTypeDef USART3RXBuf = {0,0,16,USART3RXBufAddr};

static void UsartTXGPIOConfig(uint32_t RCC_APB2Periph_GPIOx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;

	GPIO_Init(GPIOx,&GPIO_InitStructure);
}

static void UsartRXGPIOConfig(uint32_t RCC_APB2Periph_GPIOx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;

	GPIO_Init(GPIOx,&GPIO_InitStructure);
}

static void USART_NVICConfig(uint8_t NVIC_IRQChannel,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

static void UsartConfig(USART_TypeDef* USARTx,uint32_t USART_BaudRate)
{
	USART_InitTypeDef USART_InitStructure;
		
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USARTx,&USART_InitStructure);
	
	USART_ITConfig(USARTx,USART_IT_RXNE,ENABLE);
}

void USART1Init(uint32_t USART_BaudRate)
{
	UsartTXGPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_9);
	UsartRXGPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_10);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	UsartConfig(USART1,USART_BaudRate);
	USART_NVICConfig(USART1_IRQn,2,1);	
	USART_Cmd(USART1, ENABLE);
}

void USART2Init(uint32_t USART_BaudRate)
{
	UsartTXGPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_2);
	UsartRXGPIOConfig(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_3);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	UsartConfig(USART2,USART_BaudRate);
	USART_NVICConfig(USART2_IRQn,1,1);	
	USART_Cmd(USART2, ENABLE);
}

void USART3Init(uint32_t USART_BaudRate)
{
	UsartTXGPIOConfig(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_10);
	UsartRXGPIOConfig(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_11);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	UsartConfig(USART3,USART_BaudRate);
	USART_NVICConfig(USART3_IRQn,2,1);	
	USART_Cmd(USART3, ENABLE);
}

int fputc(int c, FILE *stream)
{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
		USART_SendData(USART1,(uint8_t)c);		
		return c;
}

int fgetc(FILE *stream)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
	return USART_ReceiveData(USART1);
}
/*
串口1中断服务函数
*/
void USART1_IRQHandler(void)
{	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
/*
串口2中断服务函数
*/
void USART2_IRQHandler(void)
{	
	uint8_t Data;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
	{	
		Data = USART_ReceiveData(USART2);
		WriteFIFOBuf(&USART2RXBuf,&Data,1);
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}
/*
串口3中断服务函数
*/
void USART3_IRQHandler(void)
{	
	uint8_t Data;
	if(USART_GetITStatus(USART3,USART_IT_RXNE) == SET)
	{
		Data = USART_ReceiveData(USART3);
		WriteFIFOBuf(&USART3RXBuf,&Data,1);
		UpdataRedRayRevData();
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
}


