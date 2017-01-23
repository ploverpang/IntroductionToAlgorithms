/* 一个旅行者有一个最多能用M公斤的背包，现在有N件物品，
它们的重量分别是W1，W2，...,Wn,
它们的价值分别为P1,P2,...,Pn.
若每种物品只有一件求旅行者能获得最大总价值。
输入格式：
M,N
W1,P1
W2,P2
......
输出格式：
X
*/

#include <stdio.h>

int snappack(int M, int N, int W[N], int P[N])
{
	int c[N][M]; //存储最大价值
	/* 初始化数组 */
	for(int i = 0; i < N; i++)
	       for(int j = 0; j < M; j++)
	       		c[i][j] = 0;

	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
			if(W[i] < M) // 如果当前物品重量小于背包重量
			{
				if((c[i-1][j-W[i]]+P[i]) > c[i-1][j]) // 如果j重量下，放入当前物品得到的价值比不放当前物品的价值大
				{
					/* 更新 c[i][j] */
					c[i][j] = c[i-1][j-W[i]] + P[i];

				}
				else
					c[i][j] = c[i-1][j];
			}	
			else
					c[i][j] = c[i-1][j];
	return c[N][M];
}

void main()
{
	int M, N;
	printf("Input capacity of pack M & number of things N\n");
	scanf("%d, %d\n", M, N);
	int W[N], P[N];
	printf("Input weight M and values P\n");
	for(int i = 0; i < N; i++)
		scanf("%d, %d \n", W[i], P[i]);

	int value = snappack(M, N, W, P);
	fprintf("The value is %d", value);
}
