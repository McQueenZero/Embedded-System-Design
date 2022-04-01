#include <stdlib.h>

#define NUM 100

unsigned int data[NUM];
unsigned int pos[NUM];

int main (void) {
 	
	unsigned int n;
	
	for(n=0;n<NUM;n++)
	{
		data[n]=rand()%(NUM+1);	
		pos[n] = n;		//生成原始位置数组
	}
//	BubbleSort(data, 30);			//得排序后数组
	BubbleSortNote(data, pos, 30);	//得排序后数组和排序后位置数组
	
	while (1);	
}

