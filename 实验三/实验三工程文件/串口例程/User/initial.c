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

void USARTs_init(void)
{
	//------- GPIO�˿�����	-------------------
	GPIO_InitTypeDef USART_GPIO_Init;	//���崮��GPIO��ʼ���ṹ�����
	USART_InitTypeDef USART_function_Init;	//���崮�ڳ�ʼ���ṹ�����
  
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
	USART_function_Init.USART_BaudRate = 9600;	//���ò�����Ϊ9600��������ֵ����USART_BRR
	USART_function_Init.USART_WordLength = USART_WordLength_8b;	//�������ݸ�ʽΪ8λ������USART_CR1(M)
	USART_function_Init.USART_StopBits = USART_StopBits_1;	//����1λֹͣλ������USART_CR2(STOP[1:0])
	USART_function_Init.USART_Parity = USART_Parity_No;	//����Ϊ����żУ��λ������USART_CR1(PCE)
	USART_function_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ����������������Ϊ�ޣ�����USART_CR3(CTSE)
	USART_function_Init.USART_Mode = USART_Mode_Rx| USART_Mode_Tx;	//����ģʽ�����պͷ���ʹ�ܣ�����USART_CR1(TE/RE)

	USART_Init(USART3, &USART_function_Init);	//��ʼ������3  
		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	//����3�ж�ʹ��USART_IT_RXNE���������ݼĴ��������ж�
													//USART_IT_TXE���������ݼĴ���Ϊ���ж�
	USART_Cmd(USART3, ENABLE);	//����3ʹ�ܣ�����USART_CR3(UE) 		
  
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

void initial(void)
{	
	rccset();
	USART_NVIC_init();
	USARTs_init();
}
