
/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "Nixietube.h"
#include "KEYs_Config.h"

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
  * @brief   This function handles NMI exception.
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
#define LED_light(x) ( GPIOD->BSRR |= 0x0004<<x ) //点亮某一颗LED
#define LED_Close(x) ( GPIOD->BRR |= 0x0004<<x )  //关闭某一颗LED
			
extern int sec;	extern int sec_n;
extern int min;
extern int hour;
extern unsigned int flag;
extern unsigned int alarmflag;
int j=1;
int pauseflag=1;

void TIM2_IRQHandler(void)
{	
	
	TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);	//清除TIM2定时器中断标志位
	
	sec_n=sec_n+1;	//不论什么状态，每秒自然时间+1s
	
	if(flag==0) 
	{
		sec=sec+1;	//时间自增状态下，每秒时间+1s			
		//LED灯右流水
		if(alarmflag!=1||j!=1) LED_Close(j);	//闹钟开启时第一个LED灯常亮
		j=j-1;	
		if(j<1) j=4;		
		LED_light(j);
	}
	if(flag==3)	
	{
		sec=sec-1;	//时间自减状态下，每s时间-1s		
		//LED灯左流水
		LED_Close(j);
		j=j+1;
		if(j>4) j=1;
		LED_light(j);
	}
	if(flag==1)
	{
		//时间暂停状态下，LED灯闪烁
		if(pauseflag==1){
			LED_light(1);LED_light(2);LED_light(3);LED_light(4);
			pauseflag=0;
		}	
		else{
			LED_Close(1);LED_Close(2);LED_Close(3);LED_Close(4);
			pauseflag=1;
		}		
	}
	if(flag==2)
	{
		//时间设置状态下，LED灯全常亮
		LED_light(1);LED_light(2);LED_light(3);LED_light(4);
	}
	
}

void EXTI15_10_IRQHandler(void)
{
	
	if(EXTI_GetITStatus(EXTI_Line15))
	{
		
		EXTI_ClearITPendingBit(EXTI_Line15); //清除LINE15上的中断标志位
		
		if(key1_state_check()==0)	//按下按键KEY1，计时重置、开启
		{ 
			delay_ms(150);	//消抖
			//计时器功能步骤：先按KEY1系统时间清零，再按KEY1进入时间自增状态，KEY2用作暂停/恢复计时
			if(flag==0||flag==3)
			{
				//时间自增或自减状态进入KEY1中断，清零后模式标识符置1
				sec=0;
				min=0;
				hour=0;
				flag=1;	//进入时间暂停（停止）状态				
			}
			else if(flag==1)
			{
				//停止状态进入KEY1中断，清零后模式标识符置0,开启计时
				sec=0;
				min=0;
				hour=0;				
				flag=0;	//进入时间自增 
			}
			else
			{
				//其他状态进入Key1中断，模式标识符置0
				flag=0;	//进入时间自增 
			}
			
		}
	}
	
}
