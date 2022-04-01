#include "stm32f10x.h"
#include "main.h"

extern unsigned int data;
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
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |RCC_APB2Periph_GPIOD , ENABLE);	  //RCC_APB2Periph_USART1|

	  /* Enable TIM2 clock */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

}

void gpioset(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
  	//LED1����LED4 ��Ӧ������ΪPD3����PD6
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		GPIO_ResetBits(GPIOD, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);		
		
		//PA0ΪADͨ��0
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;		 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			  
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

void adcset(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	//ADC_DeInit(ADC_TypeDef * ADC1); 
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ADCɨ��ģʽʹ��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ADC����ģʽʹ��
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//���ⲿ�¼�����
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//���������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//1��ת��ͨ��
	ADC_Init(ADC1, &ADC_InitStructure);	//�趨ADC1����
	/* ADC1 regular channels configuration */ 

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_7Cycles5);	  
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/* Enable ADC1 reset calibaration register */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));
	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	 while(ADC_GetCalibrationStatus(ADC1));
	/* Start ADC1 Software Conversion */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
	while(ADC_GetSoftwareStartConvStatus(ADC1));   
}

void dmaset(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	DMA_DeInit(DMA1_Channel1);  
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	//�趨�����ַ 
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32) & data;	//�趨�ڴ������ַ,ADת����ֵ��data����
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	//�趨����Դ����
	DMA_InitStructure.DMA_BufferSize =DMAADBUFF;	//�����ֽ�����1��1����    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//�����Ƿ�����������ڶ����裩 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�ڴ��ַ�Ƿ���������������飩
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//�������ݳ���Ϊ����
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;	//�ڴ����ݳ���Ϊ����          
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;	//DMAѭ��ģʽ
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;	//DMA���ȼ���
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;	//�����ڴ浽�ڴ�       
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);	//��ʼ��DMAͨ��
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, DISABLE);	//������DMA�ж�����
	DMA_Cmd(DMA1_Channel1, ENABLE);	//ʹ��DMAͨ��

}

void USARTs_init(void)
{
	//------- GPIO�˿�����	-------------------
	GPIO_InitTypeDef USART_GPIO_Init;
	USART_InitTypeDef USART_function_Init;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��USART3��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

 	USART_DeInit(USART3);  //��λ����3

 	//---- USART1_TX   PB10	 ----------------
  USART_GPIO_Init.GPIO_Pin = GPIO_Pin_10; 
  USART_GPIO_Init.GPIO_Speed = GPIO_Speed_50MHz;
  USART_GPIO_Init.GPIO_Mode = GPIO_Mode_AF_PP;	  //�����������
  GPIO_Init(GPIOB, &USART_GPIO_Init);               //��ʼ��PA9
   
  //-----USART1_RX   PB11	 -------------
  USART_GPIO_Init.GPIO_Pin = GPIO_Pin_11;
  USART_GPIO_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOB, &USART_GPIO_Init);                //��ʼ��PA10
 
  //--------- ��ʼ�� USART �Ĵ�������  -----------------------------
	USART_function_Init.USART_BaudRate = 9600;                   //����Ϊ9600;
	USART_function_Init.USART_WordLength = USART_WordLength_8b;   //8λ���ݸ�ʽ
	USART_function_Init.USART_StopBits = USART_StopBits_1;        //1��ֹͣλ
	USART_function_Init.USART_Parity = USART_Parity_No;           //����żУ��λ
	USART_function_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ������������
	USART_function_Init.USART_Mode = USART_Mode_Rx| USART_Mode_Tx;	 //�շ�ģʽ

  USART_Init(USART3, &USART_function_Init); //��ʼ������  
		
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //���������ж�

  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 		
  
}
	
void USART_NVIC_init(void)
{
	NVIC_InitTypeDef NVIC_function_Init; 

  //---- Usart1 NVIC �ж����� ----------------
  NVIC_function_Init.NVIC_IRQChannel = USART3_IRQn;
	NVIC_function_Init.NVIC_IRQChannelPreemptionPriority=3 ; //��ռ���ȼ�3
	NVIC_function_Init.NVIC_IRQChannelSubPriority = 3;		  //�����ȼ�3
 	NVIC_function_Init.NVIC_IRQChannelCmd = ENABLE;		  //IRQͨ��ʹ��
	NVIC_Init(&NVIC_function_Init);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���
}

void nvicset(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	  
	#ifdef  VECT_TAB_RAM  
	  /* Set the Vector Table base location at 0x20000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#else  /* VECT_TAB_FLASH  */
	  /* Set the Vector Table base location at 0x08000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif
	  
	/* Configure the Priority Group to 2 bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
}

void timerset(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//TIME2 72M	
	TIM_TimeBaseStructure.TIM_Period = 4999;//;	1s ��ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler =7199;// Ԥ��Ƶ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );
		  
	TIM_Cmd(TIM2, DISABLE);

}

void initial(void)
{	
	rccset();
	gpioset();
	adcset();
	dmaset();
	USART_NVIC_init();
	USARTs_init();
	nvicset();
	timerset();	
}
