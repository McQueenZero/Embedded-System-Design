#include <stdlib.h>

#define NUM 100		//�������������

unsigned int data[NUM];		//�����������ͣ��޷�������

int main (void) {
 	
	unsigned int n;
	
	for(n=0;n<NUM;n++)
	{
		data[n]=rand()%(NUM+1);		//rand()���������������rand()%(NUM+1)�������������0~NUM ֮�䡣
	}
	
	while (1);
}
