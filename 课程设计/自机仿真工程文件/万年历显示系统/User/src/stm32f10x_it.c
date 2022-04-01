/*******************************************************************************
** 文件名: 		stm32f10x_it.c
** 版本：  		1.0
** 工作环境: 	RealView MDK-ARM 4.20
** 作者: 		吴国炎
** 生成日期: 	2011-04-10
** 功能:		中断源文件
** 相关文件:	无
** 修改日志：	2011-04-10   创建文档
*******************************************************************************/
#include "stm32f10x_it.h"
#include "KEYs_Config.h"

/******************************************************************************/
/*            Cortex-M3 处理器的相关服务函数                                  */
/******************************************************************************/

/*******************************************************************************
  * @函数名称	NMI_Handler
  * @函数说明   不可屏蔽中断发生的中断处理函数
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
  * @函数名称	HardFault_Handler
  * @函数说明   硬件错误发生的中断处理函数
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void HardFault_Handler(void)
{
    //当硬件错误发生时进入死循环 
    while (1)
    {
    }
}

/*******************************************************************************
  * @函数名称	MemManage_Handler
  * @函数说明   内存管理中断发生的中断处理函数
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void MemManage_Handler(void)
{
    //当内存管理中断发生时进入死循环 
    while (1)
    {
    }
}

/*******************************************************************************
  * @函数名称	BusFault_Handler
  * @函数说明   总线错误发生的中断处理函数
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void BusFault_Handler(void)
{
    //当总线错误发生时进入死循环 
    while (1)
    {
    }
}

/*******************************************************************************
  * @函数名称	UsageFault_Handler
  * @函数说明   Usage 错误错误发生的中断处理函数
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void UsageFault_Handler(void)
{
    //当Usage 错误发生时进入死循环 
    while (1)
    {
    }
}

/*******************************************************************************
  * @函数名称	SVC_Handler
  * @函数说明   SVC调用中断发生的中断处理函数
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
  * @函数名称	DebugMon_Handler
  * @函数说明   调试监控中断发生的中断处理函数
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
  * @函数名称	PendSV_Handler
  * @函数说明   Pend SV中断发生的中断处理函数
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
  * @函数名称	SysTick_Handler
  * @函数说明   SysTick中断发生的中断处理函数
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x 外设 中断 服务函数                               */
/*  增加需要的外设中断函数在下面。中断的函数名字都已经在startup_stm32f10x_xx.s*/
/*  的文件中定义好了，请参照它来写。                                          */
/******************************************************************************/


//用户增加自己的中断服务程序这下面。
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

#define LED_light(x) ( GPIOD->BSRR |= 0x0004<<x ) //点亮某一颗LED
#define LED_Close(x) ( GPIOD->BRR |= 0x0004<<x )  //关闭某一颗LED
			
extern int sec, min, hour;	
extern int sec_n;
extern unsigned char flag;
extern unsigned char alarmflag;
short j=1;
unsigned char pauseflag=1;
unsigned char tmp=0;

void TIM2_IRQHandler(void)
{	
	
	TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);	//清除TIM2定时器中断标志位
	
	sec_n=sec_n+1;	//不论什么状态，每秒自然时间+1s
	
	if(flag==0) 
	{
		sec=sec+1;	//时间自增状态下，每秒时间+1s			
		//LED灯左流水
		if(alarmflag!=1||j!=1) LED_Close(j);	//闹钟开启时第一个LED灯常亮
		j=j-1;	
		if(j<1) j=4;		
		LED_light(j);
	}
	if(flag==3)	
	{
		sec=sec-1;	//时间自减状态下，每s时间-1s		
		//LED灯右流水
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

/*------按键KEY1中断,清零、开始计时、恢复自然时钟------*/
void EXTI15_10_IRQHandler(void)
{
	
	EXTI_ClearITPendingBit(EXTI_Line15); //清除LINE15上的中断标志位
	delay_ms(50);	//消抖	
		
	if(key1_state_check()==0)	//按下按键KEY1，计时重置、开启
	{ 
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
			//时间设置进入Key1中断，模式标识符置0，用于闹钟设置完恢复时钟
			flag=0;	//进入时间自增 
		}		
	}

}

/*------按键KEY2中断,计时暂停、恢复、开启倒计时------*/
void EXTI4_IRQHandler(void)
{
	
	EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE4上的中断标志位
	delay_ms(50);	//消抖	

	if(key2_state_check()==0)
	{
		if(flag==0||flag==3)
		{
			tmp=flag;
			flag=1;	//进入暂停状态
		}
		else if(flag==2)
		{
			flag=3;	//开启倒计时
		}
		else
		{
			flag=tmp;	//恢复计时状态
		}	
	}		

}
/***********************************文件结束***********************************/
