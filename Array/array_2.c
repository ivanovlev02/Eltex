#define N 5
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int arr[N];
	srand(time(NULL));

	for(int i = 0; i < N; i++)
	{
		arr[i] = rand() % 10;
	}
	for(int i = 0; i < N; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	for(int i = N - 1; i >= 0; i--)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
