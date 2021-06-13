#include <stdio.h>

int main (void)
{
	int a = 0x0000DDAABB;
	unsigned char c;

	c = (a & 0xF);
	printf("%x\n", c);//0xB
	a = (a >> 4);
	c = (a & 0xF);
	printf("%x\n", c);//0xB
	a = (a >> 4);
	c = (a & 0xF);
	printf("%x\n", c);//0xA
	a = (a >> 4);
	c = (a & 0xF);
	printf("%x\n", c);//0xA

	return 0;
}
