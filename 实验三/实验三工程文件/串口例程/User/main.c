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
		
		initial();		
		
		while(1);

}
