
#include "KEYs_Config.h"
// -------- 按键 接在 PB4,5,6,7 以及PA15	 -----------------------
//--------- 检测PA15端口状态 ---------------------
u8 key1_state_check(void)
{
	if(GPIOA->IDR&0x8000)	//判断端口输入数据寄存器
		return 1;		
	else
		return 0;
}

//--------- 检测PB4端口状态 ---------------------
u8 key2_state_check(void)
{
	if(GPIOB->IDR&0x0010)	//判断端口输入数据寄存器
		return 1;		
	else
		return 0;
}

//--------- 检测PB5端口状态 ---------------------
u8 key3_state_check(void)
{
	if(GPIOB->IDR&0x0020)	//判断端口输入数据寄存器
		return 1;		
	else
		return 0;
}

//--------- 检测PB6端口状态 ---------------------
u8 key4_state_check(void)
{
	if(GPIOB->IDR&0x0040)	//判断端口输入数据寄存器
		return 1;		
	else
		return 0;
}

//--------- 检测PB7端口状态 ---------------------
u8 key5_state_check(void)
{
	if(GPIOB->IDR&0x0080)	//判断端口输入数据寄存器
		return 1;		
	else
		return 0;
}

//--------  延时函数 ---------------
void delay_ms(u8 ms)
{
	u16 i,j;
	for(i=0; i<ms*2; i++)
	{
		for(j=0; j<8000; j++);
	}
   
}
