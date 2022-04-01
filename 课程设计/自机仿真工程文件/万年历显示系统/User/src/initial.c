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
// --- LED 引脚 -----------
// PD3,PD4 PD5,PD6;
//---- 蜂鸣器引脚----
// PB8

	//--- LED引脚初始化 ------------
	GPIO_InitTypeDef  LED_GPIO;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOD, ENABLE);	 //使能PB,PD端口时钟
	
	LED_GPIO.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	//指定引脚 PD3,4,5,6
	LED_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	LED_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &LED_GPIO);					 //根据设定参数初始化

	//---------- PB8 ----------------------------
	LED_GPIO.GPIO_Pin = GPIO_Pin_8;	    //指定引脚 PB8
	LED_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	LED_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &LED_GPIO);					 //根据设定参数初始化

	//------- 初始化LCD显示屏用到的IO ------
  GPIO_InitTypeDef  LCD_GPIO;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PD端口时钟
	
  LCD_GPIO.GPIO_Pin = GPIO_Pin_All;
  LCD_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  LCD_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOE, &LCD_GPIO);					 //根据设定参数初始化

  LCD_GPIO.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;	//指定引脚 
  LCD_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  LCD_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOC, &LCD_GPIO);					 //根据设定参数初始化		
		
  LCD_GPIO.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_12;	//指定引脚 
  LCD_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  LCD_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOD, &LCD_GPIO);					 //根据设定参数初始化	

	// -------- 按键 接在 PB4,5,6,7 以及PA15	 -----------------------
	//------ 按键端口初始化 ----------------------------
	GPIO_InitTypeDef  KEYs_GPIO;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA,PB端口时钟
		
	KEYs_GPIO.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	//指定引脚 PB4,5,6,7
	KEYs_GPIO.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
	KEYs_GPIO.GPIO_Speed = GPIO_Speed_2MHz;		 //IO口速度为2MHz
	GPIO_Init(GPIOB, &KEYs_GPIO);				 //根据设定参数初始化  

	//---------- PA15 ----------------------------
	KEYs_GPIO.GPIO_Pin = GPIO_Pin_15;	
	KEYs_GPIO.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
	KEYs_GPIO.GPIO_Speed = GPIO_Speed_2MHz;		 //IO口速度为2MHz
	GPIO_Init(GPIOA, &KEYs_GPIO);				 //根据设定参数初始化  
 
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
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//赋给 TIMx_CR1(CKD[1:0]) 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数 赋给 TIMx_CR1(DIR)
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);	//设定定时器TIM2参数 

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	//清中断标志位
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );	//允许 TIM_IT_Update 中断 
		  
	TIM_Cmd(TIM2, DISABLE);	//使能定时器 赋给 TIMx->CR1(CEN) 0:计数器停止工作；1:计数器开始工作

}

//---------- 外部中断配置 --------------------------------
void Exti_line_Init(void)
{
 
	EXTI_InitTypeDef Exti_line;
	NVIC_InitTypeDef NVIC_function;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

	//----- PA15 中断初始化配置   
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);	//PA15设为外部中断线

	Exti_line.EXTI_Line=EXTI_Line15;	//外部中断线15	
	Exti_line.EXTI_Mode = EXTI_Mode_Interrupt;	
	Exti_line.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	Exti_line.EXTI_LineCmd = ENABLE;	//使能外部中断线
	EXTI_Init(&Exti_line);	 	
 
	NVIC_function.NVIC_IRQChannel = EXTI15_10_IRQn;			    //中断通道40
	NVIC_function.NVIC_IRQChannelPreemptionPriority = 3;	//抢占优先级3 
	NVIC_function.NVIC_IRQChannelSubPriority = 1;		//子优先级2 
	NVIC_function.NVIC_IRQChannelCmd = ENABLE;				//使能中断通道
	NVIC_Init(&NVIC_function);  	  

	//----- PB4 中断初始化配置   
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);	//PB4设为外部中断线

	Exti_line.EXTI_Line=EXTI_Line4;	//外部中断线4	
	Exti_line.EXTI_Mode = EXTI_Mode_Interrupt;	
	Exti_line.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	Exti_line.EXTI_LineCmd = ENABLE;	//使能外部中断线
	EXTI_Init(&Exti_line);	 	
 
	NVIC_function.NVIC_IRQChannel = EXTI4_IRQn;			    //中断通道10
	NVIC_function.NVIC_IRQChannelPreemptionPriority = 3;	//抢占优先级3 
	NVIC_function.NVIC_IRQChannelSubPriority = 0;		//子优先级0 
	NVIC_function.NVIC_IRQChannelCmd = ENABLE;				//使能中断通道
	NVIC_Init(&NVIC_function);  	  
	
	
}

void initial(void)
{	
	rccset();
	gpioset();
	nvicset();
	timerset();	
	Exti_line_Init();
	
}
