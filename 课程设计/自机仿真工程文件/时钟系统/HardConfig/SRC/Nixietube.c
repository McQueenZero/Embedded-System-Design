
#include "Nixietube.h"


//--- ����ܶ������ ----------------------
  u8 Nixie_x[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x80}; //0-9��С���㣨��10����

//---- �������ĳһλ��ʾ���� ------	
//---  num: �ڼ�λ��data:Ҫ��ʾ������
//BSRR���˿�λ���üĴ�������16λ����д1���ö�Ӧ��ODRx���˿��������ݼĴ�����λΪ1��д0�Զ�Ӧ��ODRxλ������Ӱ��
//BRR���˿�λ��λ�Ĵ�����д1�����Ӧ��ODRxλΪ0��д0�Զ�Ӧ��ODRxλ������Ӱ��
void Nixietube_light(u8 num, u8 data)
{
	switch(num)
	{							//       �ڼ�λ                           							����0-9
		case 1: { GPIOE->BSRR |= 0x0001<<8;  GPIOE->BRR |= 0x3e00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
		case 2: { GPIOE->BSRR |= 0x0001<<9;  GPIOE->BRR |= 0x3d00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
		case 3: { GPIOE->BSRR |= 0x0001<<10; GPIOE->BRR |= 0x3b00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
		case 4: { GPIOE->BSRR |= 0x0001<<11; GPIOE->BRR |= 0x3700; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
		case 5: { GPIOE->BSRR |= 0x0001<<12; GPIOE->BRR |= 0x2f00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
		case 6: { GPIOE->BSRR |= 0x0001<<13; GPIOE->BRR |= 0x1f00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[data];  break;}
				
		default: break;
	}

}

//---- ָʾѡ�������ĳһλ��ĳλ��Ӧ��С��������� ------
void Nixietube_index(u8 num)
{
	switch(num)
	{							//       �ڼ�λ                           							����С����
		case 1: { GPIOE->BSRR |= 0x0001<<8;  GPIOE->BRR |= 0x3e00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
		case 2: { GPIOE->BSRR |= 0x0001<<9;  GPIOE->BRR |= 0x3d00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
		case 3: { GPIOE->BSRR |= 0x0001<<10; GPIOE->BRR |= 0x3b00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
		case 4: { GPIOE->BSRR |= 0x0001<<11; GPIOE->BRR |= 0x3700; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
		case 5: { GPIOE->BSRR |= 0x0001<<12; GPIOE->BRR |= 0x2f00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
		case 6: { GPIOE->BSRR |= 0x0001<<13; GPIOE->BRR |= 0x1f00; GPIOE->BRR |= 0x00ff;GPIOE->BSRR |= Nixie_x[10];  break;}
				
		default: break;
	}

}


//-------------- ��ʱ���� --------------------------
	
void delay(u16 ns)
{
	u16 i,j;
			
	for(i=0;i<ns;i++) 
	{
		for(j=0;j<8000;j++); 
	}

}


