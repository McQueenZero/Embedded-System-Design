
#include "stm32f10x.h"
#include"LED_Config.h"


// --- LED ���� -----------
// PD3,PD4 PD5,PD6;
//---- ����������----
// PB8

//--- LED���ų�ʼ�� ------------
 void LED_Init(void)
  {
 
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

  }  

