
#include "KEYs_Config.h"
// -------- ���� ���� PB4,5,6,7 �Լ�PA15	 -----------------------
//--------- ���PA15�˿�״̬ ---------------------
u8 key1_state_check(void)
{
	if(GPIOA->IDR&0x8000)	//�ж϶˿��������ݼĴ���
		return 1;		
	else
		return 0;
}

//--------- ���PB4�˿�״̬ ---------------------
u8 key2_state_check(void)
{
	if(GPIOB->IDR&0x0010)	//�ж϶˿��������ݼĴ���
		return 1;		
	else
		return 0;
}

//--------- ���PB5�˿�״̬ ---------------------
u8 key3_state_check(void)
{
	if(GPIOB->IDR&0x0020)	//�ж϶˿��������ݼĴ���
		return 1;		
	else
		return 0;
}

//--------- ���PB6�˿�״̬ ---------------------
u8 key4_state_check(void)
{
	if(GPIOB->IDR&0x0040)	//�ж϶˿��������ݼĴ���
		return 1;		
	else
		return 0;
}

//--------- ���PB7�˿�״̬ ---------------------
u8 key5_state_check(void)
{
	if(GPIOB->IDR&0x0080)	//�ж϶˿��������ݼĴ���
		return 1;		
	else
		return 0;
}

//--------  ��ʱ���� ---------------
void delay_ms(u8 ms)
{
	u16 i,j;
	for(i=0; i<ms*2; i++)
	{
		for(j=0; j<8000; j++);
	}
   
}
