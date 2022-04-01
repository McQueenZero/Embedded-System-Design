
#include "stm32f10x.h"
#include"LED_Config.h"


// --- LED 引脚 -----------
// PD3,PD4 PD5,PD6;
//---- 蜂鸣器引脚----
// PB8

//--- LED引脚初始化 ------------
 void LED_Init(void)
  {
 
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

  }  

