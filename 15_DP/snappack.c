/* һ����������һ���������M����ı�����������N����Ʒ��
���ǵ������ֱ���W1��W2��...,Wn,
���ǵļ�ֵ�ֱ�ΪP1,P2,...,Pn.
��ÿ����Ʒֻ��һ�����������ܻ������ܼ�ֵ��
�����ʽ��
M,N
W1,P1
W2,P2
......
�����ʽ��
X
*/

#include <stdio.h>

int snappack(int M, int N, int W[N], int P[N])
{
	int c[N][M]; //�洢����ֵ
	/* ��ʼ������ */
	for(int i = 0; i < N; i++)
	       for(int j = 0; j < M; j++)
	       		c[i][j] = 0;

	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
			if(W[i] < M) // �����ǰ��Ʒ����С�ڱ�������
			{
				if((c[i-1][j-W[i]]+P[i]) > c[i-1][j]) // ���j�����£����뵱ǰ��Ʒ�õ��ļ�ֵ�Ȳ��ŵ�ǰ��Ʒ�ļ�ֵ��
				{
					/* ���� c[i][j] */
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
