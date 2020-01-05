/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "LED/bsp_led.h"
#include "KEY/bsp_key.h"
#include "CONTROL/control.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void TIM2_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET) 
	{	
	TrackTarget();//����Ŀ��

		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
	}		 	
}

void TIM4_IRQHandler(void)
{
	static uint16_t i,j,k;//���ڼ�¼PA0��PA1��ƽ����ʱ��
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET) 
	{	
		Period5msKeyScan();//����ɨ��
/************�������*******************/		
		if(ShootFlag==1&&i<4)//������Ҫ4*5ms = 20ms�͵�ƽ
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			i++;
		}
		else if(i>=4)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
			ShootFlag = 0;
			i = 0;
		}
/**********������*********************/		
		if(ChargeFlag==1&&j<1000)//�����Ҫ1000*5ms = 5s�ߵ�ƽ
		{
			LED_ON;
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
			j++;
		}
		else if(j>=1000)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			ChargeFlag = 0;
			j = 0;
			LED_OFF;
		}
/************�Զ��������*********************/
		if(AotoChargeAndShootFlag==1&&k<1000)
		{
			if(k==1)
			{
				ChargeFlag = 1;
			}
			k++;
		}
		else if((k>=1000)&&(k<1200))
		{
			k++;
		}
		else if(k>=1200)
		{
			ShootFlag = 1;
			AotoChargeAndShootFlag = 0;
			k = 0;
		}
/**************************************/		
		TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);	
	}		 	
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
