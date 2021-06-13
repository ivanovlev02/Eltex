#include <stdio.h>

int main (void)
{
	int a = 0x00FFAABB, a1 = 0x00AAEEBB, b;
	unsigned char c;
	int i = 0;
	
	printf("a = %X\n", a);

	while(i <= 24){
		c = (a >> i) & 0xFF;
		printf("%X\n", c);
		if(i == 16){
			b = (a & 0xEEFFFF);
		}
		i += 8;
	}
	
	printf("\nb(a_new) = %X\n", b);
	/*
	a = a & 0xEEFFFF;
	printf("\na_new = %X\n", a);
	*/

	printf("\na1 = %X\n", a1);
	a1 = a1 | 0xFF0000;
	printf("a1(new) = %X\n", a1);

	return 0;
}
