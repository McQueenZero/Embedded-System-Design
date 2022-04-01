
#include "Nixietube.h"


//--- 数码管段码编码 ----------------------
  u8 Nixie_x[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x80}; //0-9和小数点（以10代表）

//---- 在数码管某一位显示数据 ------	
//---  num: 第几位，data:要显示的数字
//BSRR：端口位设置寄存器（低16位），写1设置对应的ODRx（端口数出数据寄存器）位为1，写0对对应的ODRx位不产生影响
//BRR：端口位复位寄存器，写1清除对应的ODRx位为0，写0对对应的ODRx位不产生影响
void Nixietube_light(u8 num, u8 data)
{
	switch(num)
	{							//       第几位                           							数字0-9
		case 1: { GPIOE->BSRR |= 0x0001<<8;  GPIOE->BRR |= 0x3e00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
		case 2: { GPIOE->BSRR |= 0x0001<<9;  GPIOE->BRR |= 0x3d00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
		case 3: { GPIOE->BSRR |= 0x0001<<10; GPIOE->BRR |= 0x3b00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
		case 4: { GPIOE->BSRR |= 0x0001<<11; GPIOE->BRR |= 0x3700; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
		case 5: { GPIOE->BSRR |= 0x0001<<12; GPIOE->BRR |= 0x2f00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
		case 6: { GPIOE->BSRR |= 0x0001<<13; GPIOE->BRR |= 0x1f00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
				
		default: break;
	}

}

//---- 指示选中数码管某一位（某位对应的小数点点亮） ------
void Nixietube_index(u8 num)
{
	switch(num)
	{							//       第几位                           							点亮小数点
		case 1: { GPIOE->BSRR |= 0x0001<<8;  GPIOE->BRR |= 0x3e00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
		case 2: { GPIOE->BSRR |= 0x0001<<9;  GPIOE->BRR |= 0x3d00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
		case 3: { GPIOE->BSRR |= 0x0001<<10; GPIOE->BRR |= 0x3b00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
		case 4: { GPIOE->BSRR |= 0x0001<<11; GPIOE->BRR |= 0x3700; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
		case 5: { GPIOE->BSRR |= 0x0001<<12; GPIOE->BRR |= 0x2f00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
		case 6: { GPIOE->BSRR |= 0x0001<<13; GPIOE->BRR |= 0x1f00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
				
		default: break;
	}

}


//-------------- 延时函数 --------------------------
	
void delay(u16 ns)
{
	u16 i,j;
			
	for(i=0;i<ns;i++) 
	{
		for(j=0;j<8000;j++); 
	}

}


