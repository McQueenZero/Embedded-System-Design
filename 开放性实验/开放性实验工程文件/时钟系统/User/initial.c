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
// --- LED ���� -----------
// PD3,PD4 PD5,PD6;
//---- ����������----
// PB8

	//--- LED���ų�ʼ�� ------------
	GPIO_InitTypeDef  LED_GPIO;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PB,PD�˿�ʱ��
	
	LED_GPIO.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	//ָ������ PD3,4,5,6
	LED_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	LED_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &LED_GPIO);					 //�����趨������ʼ��

	//---------- PB8 ----------------------------
	LED_GPIO.GPIO_Pin = GPIO_Pin_8;	    //ָ������ PB8
	LED_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	LED_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &LED_GPIO);					 //�����趨������ʼ��

	//------- ��ʼ��������õ���IO ------
	GPIO_InitTypeDef  Nixietube_GPIO;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PE�˿�ʱ��
	
	Nixietube_GPIO.GPIO_Pin = 0x3fff;	//PE0 - PE15
	Nixietube_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	Nixietube_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &Nixietube_GPIO);				 //�����趨������ʼ��

	// -------- ���� ���� PB4,5,6,7 �Լ�PA15	 -----------------------
	//------ �����˿ڳ�ʼ�� ----------------------------
	GPIO_InitTypeDef  KEYs_GPIO;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA,PB�˿�ʱ��
		
	KEYs_GPIO.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	//ָ������ PB4,5,6,7
	KEYs_GPIO.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
	KEYs_GPIO.GPIO_Speed = GPIO_Speed_2MHz;		 //IO���ٶ�Ϊ2MHz
	GPIO_Init(GPIOB, &KEYs_GPIO);				 //�����趨������ʼ��  

	//---------- PA15 ----------------------------
	KEYs_GPIO.GPIO_Pin = GPIO_Pin_15;	
	KEYs_GPIO.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
	KEYs_GPIO.GPIO_Speed = GPIO_Speed_2MHz;		 //IO���ٶ�Ϊ2MHz
	GPIO_Init(GPIOA, &KEYs_GPIO);				 //�����趨������ʼ��  
 
}

void nvicset(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;	//�����жϳ�ʼ���ṹ�����
	  
	#ifdef  VECT_TAB_RAM  
	  /* Set the Vector Table base location at 0x20000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#else  /* VECT_TAB_FLASH  */
	  /* Set the Vector Table base location at 0x08000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif
	  
	/* Configure the Priority Group to 2 bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�ܹ�4λ���ȼ�λ�����������ȼ������ȼ���NVIC_PriorityGroup_2 Ϊ 2 λ�����ȼ� 2 λ�����ȼ���

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	//�趨�ж�ԴΪTIM2_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//�趨�ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�趨�ж������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);	//��ʼ���ж�
	
}

void timerset(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	//���嶨ʱ����ʼ���ṹ�����
	
	//TIME2 72M	
	TIM_TimeBaseStructure.TIM_Period = 9999;	//1s	��ʱ���� ����TIMx_ARR
	TIM_TimeBaseStructure.TIM_Prescaler =7199;	//Ԥ��Ƶ��ֵ ����TIMx_PSC
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//���� TIMx_CR1(CKD[1:0]) 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ��� ���� TIMx_CR1(DIR)
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);	//�趨��ʱ��TIM2���� 

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	//���жϱ�־λ
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );	//���� TIM_IT_Update �ж� 
		  
	TIM_Cmd(TIM2, DISABLE);	//ʹ�ܶ�ʱ�� ���� TIMx->CR1(CEN) 0:������ֹͣ������1:��������ʼ����

}

//---------- �ⲿ�ж����� --------------------------------
void Exti_line_Init(void)
{
 
	EXTI_InitTypeDef Exti_line;
	NVIC_InitTypeDef NVIC_function;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

	//----- PA15 �жϳ�ʼ������   
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);	//PA15��Ϊ�ⲿ�ж���

	Exti_line.EXTI_Line=EXTI_Line15;	//�ⲿ�ж���15	
	Exti_line.EXTI_Mode = EXTI_Mode_Interrupt;	
	Exti_line.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	Exti_line.EXTI_LineCmd = ENABLE;	//ʹ���ⲿ�ж���
	EXTI_Init(&Exti_line);	 	
 
	NVIC_function.NVIC_IRQChannel = EXTI15_10_IRQn;			    //�ж�ͨ��6
	NVIC_function.NVIC_IRQChannelPreemptionPriority = 3;	//��ռ���ȼ�3 
	NVIC_function.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0 
	NVIC_function.NVIC_IRQChannelCmd = ENABLE;				//ʹ���ж�ͨ��
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
