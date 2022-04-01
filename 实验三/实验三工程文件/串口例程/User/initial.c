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
	//------- GPIO端口设置	-------------------
	GPIO_InitTypeDef USART_GPIO_Init;	//定义串口GPIO初始化结构体变量
	USART_InitTypeDef USART_function_Init;	//定义串口初始化结构体变量
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能USART3，GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

 	USART_DeInit(USART3);  //复位串口3

 	//---- USART1_TX   PB10	 ----------------
	USART_GPIO_Init.GPIO_Pin = GPIO_Pin_10; 
	USART_GPIO_Init.GPIO_Speed = GPIO_Speed_50MHz;
	USART_GPIO_Init.GPIO_Mode = GPIO_Mode_AF_PP;	  //复用推挽输出
	GPIO_Init(GPIOB, &USART_GPIO_Init);               //初始化PA9
   
    //-----USART1_RX   PB11	 -------------
	USART_GPIO_Init.GPIO_Pin = GPIO_Pin_11;
	USART_GPIO_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOB, &USART_GPIO_Init);                //初始化PA10
 
    //--------- 初始化 USART 寄存器功能  -----------------------------
	USART_function_Init.USART_BaudRate = 9600;	//设置波特率为9600计算后的数值赋给USART_BRR
	USART_function_Init.USART_WordLength = USART_WordLength_8b;	//设置数据格式为8位，赋给USART_CR1(M)
	USART_function_Init.USART_StopBits = USART_StopBits_1;	//设置1位停止位，赋给USART_CR2(STOP[1:0])
	USART_function_Init.USART_Parity = USART_Parity_No;	//设置为无奇偶校验位，赋给USART_CR1(PCE)
	USART_function_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件数据流控制设置为无，赋给USART_CR3(CTSE)
	USART_function_Init.USART_Mode = USART_Mode_Rx| USART_Mode_Tx;	//串口模式，接收和发送使能，赋给USART_CR1(TE/RE)

	USART_Init(USART3, &USART_function_Init);	//初始化串口3  
		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	//串口3中断使能USART_IT_RXNE，接收数据寄存器不空中断
													//USART_IT_TXE，发送数据寄存器为空中断
	USART_Cmd(USART3, ENABLE);	//串口3使能，赋给USART_CR3(UE) 		
  
}
	
void USART_NVIC_init(void)
{
	NVIC_InitTypeDef NVIC_function_Init; 

	//---- Usart1 NVIC 中断配置 ----------------
	NVIC_function_Init.NVIC_IRQChannel = USART3_IRQn;
	NVIC_function_Init.NVIC_IRQChannelPreemptionPriority=3 ; //抢占优先级3
	NVIC_function_Init.NVIC_IRQChannelSubPriority = 3;		  //子优先级3
	NVIC_function_Init.NVIC_IRQChannelCmd = ENABLE;		  //IRQ通道使能
	NVIC_Init(&NVIC_function_Init);	//根据指定的参数初始化NVIC寄存器
}

void initial(void)
{	
	rccset();
	USART_NVIC_init();
	USARTs_init();
}
