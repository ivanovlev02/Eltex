#define N 7
#include <stdio.h>

int main(void)
{
	int n = 1;
	//int k = 5;
	int a[N][N];
	int nsqr = N*N;
	int i = 0, j = N / 2;

	while(n <= nsqr)
	{
		a[i][j] = n;
		i--;
		j++;
		if(n % N == 0)
		{
			i += 2;
			--j;
		}else
		{
			if(j == N)
			{
				j -= N;
			}else if( i < 0)
			{
				i += N;
			}
		}
		//k++;
		n++;
	}
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++){
			printf("%02d ", a[i][j]);
		}
		printf("\n");
	}

	return 0;
}
