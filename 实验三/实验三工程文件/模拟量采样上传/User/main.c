#include "stm32f10x.h"
#include "main.h"

void initial(void);

void delay (unsigned int dly)
{
	unsigned int i;
	
	
	for ( ; dly>0; dly--)
		for (i=0; i<50000; i++);
}

unsigned int data;
unsigned int flag=0;	//0.5秒高低位轮发标志位
unsigned int sendflag=1;	//发送完成标志位
unsigned int data_l;	//数据低8位
unsigned int data_h;	//数据高8位

int main(void)
{
		
		unsigned int i;
		initial();		
		TIM_Cmd(TIM2, ENABLE);
	
		while(1)
		{
			
			if(data<820)i = 0;
			if(data>=820&&data<1640)i = 0x8;
			if(data>=1640&&data<2460)i = 0x18;
			if(data>=2460&&data<3280)i = 0x38;
			if(data>=3280)i = 0x78;
			
			GPIOD->ODR =i;					
			
			if(sendflag==1)
			{	
				data_l=data&0xff;	//获取data低8位
				data_h=(data>>8)&0xff;	//获取data高8位
				sendflag=0;	//进入发送状态
				//设置sendflag是为了保证，
				//1s周期内先高4位后低8位均发送完成后，
				//再读取下一次的AD转换数值，保证12位数据的完整性
			}
		}

}
