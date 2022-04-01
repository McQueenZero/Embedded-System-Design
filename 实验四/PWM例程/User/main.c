#include "stm32f10x.h"

#define KEYSTART 0xe  //K2  PB4
#define KEYSTOP  0xd  //K3  PB5
//#define KEYNEXT  0xb  //K4  PB6
//#define KEYLAST  0x7  //K7  PB7
#define NUMD 0
#define NUMT 1
#define NUMS 2
#define NUMC 79
#define LENGTH 100
#define SPEED 4
#define VOLUME 4

unsigned char key=0xf;
unsigned char keybak=0xf;
//int songNum=0;//歌曲数量
unsigned int numD=0;//音符延长时间
unsigned int numT=0;//音符周期 
unsigned int numS=0;//音符强度
unsigned int numC=0;//音符计数
unsigned int count[3]={0};//计数变量

const int song[3][LENGTH]={{6250,6250,12500,   12500,12500,12500,6250,6250,6250,   6250,12500,18750,6250,6250,   6250,12500,12500,12500,6250,   25000,6250,6250,6250,   12500,12500,12500,6250,6250,   6250,12500,12500,6250,6250,6250,   6250,12500,6250,6250,6250,6250,   6250,25000,6250,12500,18750,   12500,12500,6250,6250,   6250,25000,6250,6250,6250,   6250,18750,6250,12500,6250,   25000,6250,6250,6250,18750,  6250,6250,18750,6250,   6250,31250,6250,6250,   6250,12500,12500,12500,6250,50000,   50000,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
												   {255, 152, 170,     191,  191,  191,  191, 227, 255,    128, 114,  114,  191, 170,    152, 128,  128,  191,  170,    170,  170, 170, 191,    100,  191,  191,  227, 255,    128, 114,  114,  191, 191, 170,    152, 128,  255, 128, 152, 170,    170, 170,  152, 170,  191,     191,  191,  227, 255,    128, 114,  191, 191, 170,    152, 128,  128, 191,  170,    170,  100, 170, 152, 191,    191, 191, 191,  227,    125, 114,  191, 170,    152, 128,  128,  152,  170, 170,     100,     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
												   {128, 46,  68,      96,   58,   77,   58,  68,  77,     64,  34,   46,   58,  51,     76,  38,   51,   58,   51,     85,   51,  68,  58,     0,    96,   58,   68,  77,     64,  57,   34,   58,  77,  51,     76,  38,   102, 38,  46,  51,     85,  51,   61,  51,   58,      96,   58,   91,  77,     64,  34,   77,  58,   51,    76,  38,   51,  58,   85,     51,   0,   68,  46,  58,     96,  58,  77,   68,     64,  34,   77,  51,     76,  38,   51,   46,   85,  51,      0,       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

void PwmPinSet(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //设定PB时钟
	
  //PWM对应的引脚为PB8
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
}
void KeyPinSet(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //设定PB时钟
	
  //PWM对应的引脚为PB8
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);		 	
}
void LedPinSet(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //设定PD时钟
	
  //LED1——LED4 对应的引脚为PD3——PD6
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
}
void Tim2Set(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	 /* Enable TIM2 clock */
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	
	//TIME2 72M	
	TIM_TimeBaseStructure.TIM_Period = 9;//0.00001s
	TIM_TimeBaseStructure.TIM_Prescaler =71;// 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );
		  
	TIM_Cmd(TIM2, DISABLE);	
}
void NvicSet(void)
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
void TIM2_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
	count[NUMD]++;
	count[NUMT]++;
	count[NUMS]++;				
	if(count[NUMS]<=numS)//判断音强计数值是否超过音强设定值
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_8);//设置引脚输出为高电平
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);//设置引脚输出为低电平
	}
	if(count[NUMT]>numT)//判断音符周期计数值是否超过音符周期设定值
	{
		count[NUMS]=0;
		count[NUMT]=0;
	
		if(count[NUMD]>numD)//判断音符延长计数值是否超过音符延长设定值
		{
			count[NUMD]=0;
			numC++;	
			if(numC>=NUMC)//判断歌曲是否播放到结尾
			{
				numC=0;	
				TIM_Cmd(TIM2, DISABLE);//关定时器
				GPIO_ResetBits(GPIOB,GPIO_Pin_8);//引脚设定低电平				
			}
			numD=song[NUMD][numC]*SPEED;//设定音符延迟时间					
			numT=song[NUMT][numC];//设定音符周期时间
			numS=song[NUMS][numC]/VOLUME;	//设定音符音强		
		}
	}
}
int main(void)
{
	PwmPinSet();
	KeyPinSet();
	LedPinSet();
	Tim2Set();
	NvicSet();
	
	numD=song[NUMD][0];
	numT=song[NUMT][0];
	numS=song[NUMS][0];
	numC=0;	
	count[NUMD]=0;
	count[NUMT]=0;
	count[NUMS]=0;
	
	while (1) 
	{   
		key=(GPIO_ReadInputData(GPIOB)>>4)&0xf;			 //读取按键
		if(keybak!=key) //判断按键是否与上次不同
		{
			keybak=key;
			GPIOD->ODR = 0;//熄灭LED灯
			switch(key)
			{
				case KEYSTART:
					TIM_Cmd(TIM2, ENABLE);	//打开定时器
					GPIOD->ODR = 0x8;
					break;
				case KEYSTOP:
					TIM_Cmd(TIM2, DISABLE);	//关闭定时器
					GPIOD->ODR = 0x10;
					numD=song[NUMD][0]*SPEED;
					numT=song[NUMT][0];
					numS=song[NUMS][0]/VOLUME;
					numC=0;	
					count[NUMD]=0;
					count[NUMT]=0;
					count[NUMS]=0;				
					break;
//				case KEYNEXT:
//					
//					break;
//				case KEYLAST:
//					
//					break;				
			}
		}		
	}	
	
}
