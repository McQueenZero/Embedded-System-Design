#include "stm32f10x.h"

void initial(void);

unsigned int flag=0;
int i=0x8;

int main(void)
{
		initial();		
		TIM_Cmd(TIM2, ENABLE);
		while(1);
}
