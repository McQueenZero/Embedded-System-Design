#include "stm32f10x.h"

void delay (unsigned int dly)
{
	unsigned int i;
	
	
	for ( ; dly>0; dly--)
		for (i=0; i<50000; i++);
}

 void LED_Init(void)
  {
 
    GPIO_InitTypeDef  GPIO_InitStructure;	//�������ų�ʼ���ṹ�����
 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��GPIOD�˿ڵ�ʱ��
	
  	//LED1����LED4 ��Ӧ������ΪPD3����PD6
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�����������ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;	//���������ٶ�Ϊ10MHz
		GPIO_Init(GPIOD, &GPIO_InitStructure);	//��ʼ��GPIOD�˿�

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
