#include <stdio.h>
__asm void my_strcpy(const char *src, char *dst)
{    
loop 	LDRB  r2, [r0], #1  //R0�����һ������
			STRB  r2, [r1], #1  //R1����ڶ�������
			CMP   r2, #0
			BNE   loop
			BLX    lr  //����ָ����Ҫ�ֶ�����
}
int main(void)
{
  const char *a = "Hello world!";
  char b[20];
  my_strcpy (a, b);
  printf("Original string: '%s'\n", a);
  printf("Copied   string: '%s'\n", b);
  return 0;
}