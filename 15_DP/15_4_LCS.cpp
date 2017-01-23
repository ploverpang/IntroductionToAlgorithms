#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>

using namespace std;

#define LEFT_UP (0)
#define UP		(1)
#define LEFT	(2)

static stack<int> solveLCS(vector<int> &X, vector<int> &Y)
{
	int m = X.size();
	int n = Y.size();

	int *c = (int*)malloc(sizeof(int)*m*n);
	int *b = (int*)malloc(sizeof(int)*m*n);
	// set lut[0,j]=0 
	for (int i = 0; i < n; i++)
		c[i] = 0;
	// set lut[i,0]=0
	for (int i = 0; i < m; i++)
		c[i*n] = 0;

	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (X[i] == Y[j])
			{
				c[i*n + j] = c[(i - 1)*n + j - 1] + 1;
				b[i*n + j] = LEFT_UP;
			}

			else
			{
				if (c[(i - 1)*n + j] > c[i*n + j - 1])
				{
					c[i*n + j] = c[(i - 1)*n + j];
					b[i*n + j] = UP;
				}
				else
				{
					c[i*n + j] = c[i*n + j - 1];
					b[i*n + j] = LEFT;
				}
			}
		}
	}

	stack<int> LCS_result;
	int i = m-1;
	int j = n-1;

	LCS_result.push(X[i]);
	// not check b look-up-table to get LCS
	do {
		if (c[(i-1)*n + j-1] == c[(i-1)*n+j] && c[(i - 1)*n + j - 1] == c[i*n + j-1])
		{
			i--;
			j--;
			LCS_result.push(X[i]);
		}
		else if (c[(i-1)*n + j] > c[i*n + j - 1])  //up > left
			i--;
		else
			j--;
	} while (i*n + j > 0);

	/*do {
		if (b[i*n + j] == LEFT_UP)
		{
			LCS_result.push(X[i]);
			i--;
			j--;
		}
		else if (b[i*n + j] == LEFT)
			j--;
		else
			i--;
	} while (i*n + j > 0);*/

	assert(i*n + j == 0);
	assert(LCS_result.size() == c[m*n - 1]);

	free(c);
	free(b);

	return LCS_result;
}

int main()
{
	int x[] = { 1,0,0,1,0,1,0,1 };
	int y[] = { 0,1,0,1,1,0,1,1,0 };

	vector<int> X(x, x+sizeof(x) / sizeof(int));
	vector<int> Y(y, y + sizeof(y) / sizeof(int));

	stack<int> result = solveLCS(X, Y);

	while(result.empty() == false)
	{
		cout << result.top() << "\t";
		result.pop();
	}
	cout << endl;
	system("PAUSE");
	return 0;
}