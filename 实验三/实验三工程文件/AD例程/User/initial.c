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
	  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

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
	ADC_InitTypeDef ADC_InitStructure;	//����ADC��ʼ���ṹ�����
	//ADC_DeInit(ADC_TypeDef * ADC1); 
	/* ADC1 configuration ------------------------------------------------------*/
	/* ADC1 �趨 ---------------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//����ģʽ������ADC_CR1(DUALMOD[3:0])
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ɨ��ģʽʹ�ܣ�����ADC_CR1(SCAN)
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//����ģʽʹ�ܣ�����ADC_CR2(CONT)
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//���ⲿ����������ADC_CR2(EXTSEL[2:0])
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//�������ݿ��Ҷ��룬����ADC_CR2(ALIGN)
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//ת��ͨ����������ADC_SQR1(L[3:0])
	ADC_Init(ADC1, &ADC_InitStructure);	//�趨ADC1����
	/* ADC1 regular channels configuration */ 
	/* ADC1 ����ͨ���趨*/

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_7Cycles5);	//�趨ת��ͨ��ֵ����ADC_SQR1(SQ1[4:0])	  
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);	//ADC1ͨ����DMAʹ��ADC_CR2(DMA)
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);	//ADC1ʹ�ܣ�����ADC_CR2(ADON)
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
	DMA_InitTypeDef DMA_InitStructure;	//����DMA��ʼ���ṹ�����

	DMA_DeInit(DMA1_Channel1);	//��λDMAͨ��
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	//�趨�����ַ������DMA_CPAR      
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32) & data;	//�趨�ڴ��ַ������DMA_CMAR
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	//�趨���ݷ��򣬸���DMA_CCR(DIR)
	DMA_InitStructure.DMA_BufferSize =DMAADBUFF;	//�����ֽ��������� DMA_CNDTR    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//�����Ƿ����������DMA_CCR(PINC) 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�ڴ��ַ�Ƿ����������DMA_CCR(MINC)
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//�������ݳ��ȣ�����DMA_CCR(PSIZE[1:0])��12λAD��ֵ  
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;	//�ڴ����ݳ��ȣ�����DMA_CCR(MSIZE[1:0])��16λdata����
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;	//DMA�Ƿ���ѭ��ģʽ������DMA_CCR(CIRC)     
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;	//DMA���ȼ�������DMA_CCR(PL[1:0])
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;	//�Ƿ����ڴ浽�ڴ��ģʽ������DMA_CCR(MEM2MEM)
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);	//��ʼ��DMAͨ��
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, DISABLE);	//������DMA�ж����󣬸���DMA_CCR(TCIE)
	DMA_Cmd(DMA1_Channel1, ENABLE);	//ʹ��DMAͨ��������DMA_CCR(EN)
}

void initial(void)
{	
	rccset();
	gpioset();
	adcset();
	dmaset();
}
