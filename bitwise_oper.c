#include <stdio.h>

int main (void)
{
	int a = 0x0000DDAABB;
	unsigned char c;

	c = (a >> 4);
	printf("%x\n", c);

	return 0;
}
