#include <stdlib.h>

#define NUM 100

unsigned int data[NUM];
unsigned int pos[NUM];

int main (void) {
 	
	unsigned int n;
	
	for(n=0;n<NUM;n++)
	{
		data[n]=rand()%(NUM+1);	
		pos[n] = n;		//����ԭʼλ������
	}
//	BubbleSort(data, 30);			//�����������
	BubbleSortNote(data, pos, 30);	//�����������������λ������
	
	while (1);	
}

