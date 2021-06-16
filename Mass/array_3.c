#define N 3
#include <stdio.h>

int main(void)
{
	int arr[N][N];

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if((i + j < N) && ((i == j) || (i < j) || (j < i)))
			{
				arr[i][j] = 1;
			}
			else
			{
				arr[i][j] = 0;
			}
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
