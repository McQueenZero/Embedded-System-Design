#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
int		a=1, b=1, n, tmp;
void	main(void){
			n=0;
			printf("%10d\n", b);
			printf("%10d\n", a);
			while((tmp = a + b) > 0 ){
				b = a;
				a = tmp;
				if(a > 1000){
					n++;
				}
				printf("%10d\n", a);
			}
			printf("\n大于1000的值的数量是%d\n", n);
			printf("最终值是：a=0x%08X b=0x%08X tmp=0x%08X\n",a,b,tmp);
			exit(0);
}