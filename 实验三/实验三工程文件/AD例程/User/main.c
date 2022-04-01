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

int main(void)
{
		
		unsigned int i;
	
		initial();		
		
		while(1)
		{
			
			if(data<820)i = 0;
			if(data>=820&&data<1640)i = 0x8;
			if(data>=1640&&data<2460)i = 0x18;
			if(data>=2460&&data<3280)i = 0x38;
			if(data>=3280)i = 0x78;
			
			GPIOD->ODR =i;
			
			delay(30);
		}

}
