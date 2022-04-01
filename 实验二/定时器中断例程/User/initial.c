#include "stm32f10x.h"

static __IO ErrorStatus HSEStartUpStatus = SUCCESS;

void rccset(void)
{
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);		//

	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus == SUCCESS)
	{
	    ///* PLLCLK = 12MHz(HSE) * 6 = 72MHz */
	    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		
	}
	else
	{
	    /* PLLCLK = 4MHz(HSI/2) * 16 = 64 MHz */
	    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16); 
		//accieflag=RCCTIME_HSI; 		  	
	}
     	/* Enable Prefetch Buffer */
	    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	
	    /* Flash 2 wait state */
	    FLASH_SetLatency(FLASH_Latency_2);
 
	    /* HCLK = SYSCLK */
	    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
	
	    /* PCLK1 = HCLK/2 36M*/
	    RCC_PCLK1Config(RCC_HCLK_Div2);
	 
	   /* PCLK2 = HCLK 72M*/
	    RCC_PCLK2Config(RCC_HCLK_Div1); 
	 
	    /* ADCCLK = PCLK2/6 =12M */
	    RCC_ADCCLKConfig(RCC_PCLK2_Div6); //AD CLOCK 12M
 	
	    /* Enable PLL */ 
	    RCC_PLLCmd(ENABLE);
	
	    /* Wait till PLL is ready */
	    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

	    /* Select PLL as system clock source */
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
	    /* Wait till PLL is used as system clock source */
	    while(RCC_GetSYSCLKSource() != 0x08);
	
	/* Enable peripheral clocks --------------------------------------------------*/
	
	  /* Enable SRAM|FLITF|DMA clock */
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SRAM |RCC_AHBPeriph_FLITF |RCC_AHBPeriph_DMA1, ENABLE);
	
	  /* Enable GPIOD clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);	  //RCC_APB2Periph_USART1|

	  /* Enable TIM2 clock */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

}

void gpioset(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  	//LED1——LED4 对应的引脚为PD3——PD6
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		GPIO_ResetBits(GPIOD, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);		
}

void nvicset(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;	//定义中断初始化结构体变量 
	  
	#ifdef  VECT_TAB_RAM  
	  /* Set the Vector Table base location at 0x20000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#else  /* VECT_TAB_FLASH  */
	  /* Set the Vector Table base location at 0x08000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif
	  
	/* Configure the Priority Group to 2 bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//总共4位优先级位，划分主优先级副优先级，NVIC_PriorityGroup_2 为 2 位主优先级 2 位副优先级。
													
	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	//设定中断源为TIM2_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//设定中断优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //设定中断子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//中断使能
	NVIC_Init(&NVIC_InitStructure);	//初始化中断
	
}

void timerset(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	//定义定时器初始化结构体变量
	
	//TIME2 72M	
	TIM_TimeBaseStructure.TIM_Period = 9999;	//1s	定时周期 赋给TIMx_ARR
	TIM_TimeBaseStructure.TIM_Prescaler =7199;	//预分频数值 赋给TIMx_PSC
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//赋给 TIMx_CR1(CKD[1:0]) 数字滤波时会用到
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数 赋给 TIMx_CR1(DIR)
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);	//设定定时器TIM2参数 

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	//清中断标志位
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );	//允许 TIM_IT_Update 中断 
		  
	TIM_Cmd(TIM2, DISABLE);	//使能定时器 赋给 TIMx->CR1(CEN) 0:计数器停止工作；1:计数器开始工作 

}

void initial(void)
{	
	rccset();
	gpioset();
	nvicset();
	timerset();	
		
}
