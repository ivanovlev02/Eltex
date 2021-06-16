#define N 6
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int arr[N][N];
	srand(time(NULL));

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			arr[i][j] = rand() % 90 + 10;
		}
	}
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf(" %d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}
