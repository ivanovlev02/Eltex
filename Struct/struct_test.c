#include <stdio.h>
#include <stdlib.h>

/*
struct test {
	unsigned char a:1;
	unsigned char b:1;
	unsigned char c:1;
	unsigned char d:1;
	unsigned char e:1;
	unsigned char f:1;
	unsigned char g:1;
	unsigned char h:1;
};
*/

/*
union test {
	char a;
	int b;
};
*/
/*
enum colors {
	RED = 2,
	GREEN = 9,
	BLUE,
	YELLOW,
	PURPLE = 25,
	VIOLET = 15,
	ORANGE
};
*/

struct test {
	char fio[20];
	long num;
} tel1, tel2;

int main(void) {
/*	char t = 0b11011001;//217

	struct test *ptr;
	ptr = (struct test*)&t;
	ptr->b = 1;
	ptr->a = 0;
	printf("%d\n", t);
*/
/*
	union test my;
	my.a = 'A';
	my.b = 12345;

	printf("%c\n", my.a);
*/	
/*	enum colors color;
	color = YELLOW;
	printf("%d\n", color);
*/
	puts("FIO: ");
	gets(tel1.fio);
	puts("\nNumber: ");
	scanf("%ld", &tel1.num);
	tel2 = tel1;
	puts("\nAdded:\n");
	printf("Last Name: %s\nNumber: %ld\n", tel2.fio, tel2.num);


	return 0;
}
