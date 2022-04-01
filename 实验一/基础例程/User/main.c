#include <stdlib.h>

#define NUM 100		//定义随机数个数

unsigned int data[NUM];		//声明数组类型：无符号整数

int main (void) {
 	
	unsigned int n;
	
	for(n=0;n<NUM;n++)
	{
		data[n]=rand()%(NUM+1);		//rand()函数生成随机数，rand()%(NUM+1)产生的随机数在0~NUM 之间。
	}
	
	while (1);
}
