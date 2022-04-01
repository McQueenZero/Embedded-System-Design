#include "stm32f10x.h"

void delay (unsigned int dly)
{
	unsigned int i;
	
	
	for ( ; dly>0; dly--)
		for (i=0; i<50000; i++);
}

 void LED_Init(void)
  {
 
    GPIO_InitTypeDef  GPIO_InitStructure;	//定义引脚初始化结构体变量
 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能GPIOD端口的时钟
	
  	//LED1——LED4 对应的引脚为PD3——PD6
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//设置推挽输出模式
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	//设置引脚速度为10MHz
		GPIO_Init(GPIOD, &GPIO_InitStructure);	//初始化GPIOD端口

  }  


int main(void)
{
		int i=0x8;
	
		LED_Init();
		
		GPIOD->ODR = i;
	
		while(1)
		{
			i<<=1;
			if(i>0x40)i=0x8;
			GPIOD->ODR = i;
			delay(30);
		}
	
}
