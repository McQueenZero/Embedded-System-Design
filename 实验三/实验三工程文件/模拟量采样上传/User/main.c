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
unsigned int flag=0;	//0.5��ߵ�λ�ַ���־λ
unsigned int sendflag=1;	//������ɱ�־λ
unsigned int data_l;	//���ݵ�8λ
unsigned int data_h;	//���ݸ�8λ

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
				data_l=data&0xff;	//��ȡdata��8λ
				data_h=(data>>8)&0xff;	//��ȡdata��8λ
				sendflag=0;	//���뷢��״̬
				//����sendflag��Ϊ�˱�֤��
				//1s�������ȸ�4λ���8λ��������ɺ�
				//�ٶ�ȡ��һ�ε�ADת����ֵ����֤12λ���ݵ�������
			}
		}

}
