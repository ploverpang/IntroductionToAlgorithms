#include <iostream>
#include <stdlib.h>

#define ESP (1e-5)

using namespace std;

void LUP(double **M, const int n, double **L, double **U, int *P)
{
	// copy M to M_copy
	double *data = new double[n*n];
	double **M_copy = new double*[n];
	int cnt = 0;
	for(int i=0; i<n; i++)
	{
		M_copy[i] = &data[cnt];
		for(int j=0; j<n; j++, cnt++)
		{
			data[cnt] = M[i][j];
		}
	}

	// initial P
	for(int i=0; i<n; i++)
	{
		P[i] = i;
	}

	for(int i=0; i<n; i++)
	{
		// find max M[i][i]
		int maxIdx = i;
		double maxMii = M[i][i];
		for(int j=i+1; j<n; j++)
		{
			if(M_copy[i][i] > maxMii)
			{
				maxMii = M_copy[i][i];
				maxIdx = j;
			}
		}
		if(maxMii < ESP)
		{
			cerr << "error" << endl;
			return;
		}
		else
		{
			swap(P[i], P[maxIdx]);
			for(int j=0; j<n; j++)
			{
				swap(M_copy[i][j], M_copy[maxIdx][j]);
			}
		}

		L[i][i] = 1;
		U[i][i] = M_copy[i][i];
		for(int j=i+1; j<n; j++)
		{
			L[j][i] = M_copy[j][i]/M_copy[i][i];
			L[i][j] = 0;
			U[i][j] = M_copy[i][j];
			U[j][i] = 0;
		}

		for(int j=i+1; j<n; j++)
		{
			for(int k=i+1; k<n; k++)
			{
				M_copy[j][k] -= U[i][k]*L[j][i];
			}
		}
	}

	delete [] M_copy;
	delete [] data;
}

// Ly = Pb, to solve y;
void forwardSolve(double **L, const int *P, const double *b, const int n, double *y)
{
	// compute Pb
	double *Pb = new double[n];
	for(int i=0; i<n; i++)
	{
		Pb[P[i]] = b[i];
	}

	// compute y
	y[0] = Pb[0];
	for(int i=1; i<n; i++)
	{
		double multiAcc = 0;
		for(int j=0; j<i; j++)
		{
			multiAcc += L[i][j]*y[j];
		}
		y[i] = Pb[i] - multiAcc;
	}
	delete [] Pb;
}

// y = Ux, compute x
void inverseSolve(double **U, const double *y, const int n, double *x)
{
	for(int i=n-1; i>=0; i--)
	{
		double multiAcc = 0;
		for(int j=n-1; j>i; j--)
		{
			multiAcc += U[i][j]*x[j];
		}
		x[i] = (y[i] - multiAcc)/U[i][i];
	}
}

void solveLinearEquation(double **A, double *x, double *b)
{

}

// A is m*p, B is p*n, C is m*n
void matrixMulti(double **A, double **B, double **C, int m, int p, int n)
{
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			double val = 0;
			for(int k=0; k<p; k++)
			{
				val += A[i][k]*B[k][j];
			}
			C[i][j] = val;
		}
	}
}

void geneRandomMatrix(double **M, const int m, const int n, const int maxVal)
{
	for(int i = 0; i< m; i++)
	{
		for(int j=0; j<n; j++)
		{
			M[i][j] = (double)(rand()%maxVal);
		}
	}
}

void printMatrix(double **M, const int m, const int n)
{
	for(int i = 0; i< m; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout << M[i][j] << '\t';
		}
		cout << endl;
	}
}

int main()
{
	const int n=4;
	double A[n][n], U[n][n], L[n][n], MultiResult[n][n];
	double *AP[n], *UP[n], *LP[n], *MP[n];
	int P[4];
	double b[n];
	double y[n];
	double x[n];
	for(int i=0; i<n; i++)
	{
		AP[i] = &A[i][0];
		UP[i] = &U[i][0];
		LP[i] = &L[i][0];
		MP[i] = &MultiResult[i][0];
		b[i] = (i+1)*100;
	}

	geneRandomMatrix(&(AP[0]), n, n, 100);
	LUP(&(AP[0]), n, &(LP[0]), &(UP[0]), P);

	forwardSolve(&(LP[0]), P, b, n, y);
	inverseSolve(&(UP[0]), y, n, x);

	printMatrix(&(AP[0]), n, n);

	// varify solve is correct
	for(int i=0; i<n; i++)
	{
		double res = 0;
		for(int j=0; j<n; j++)
		{
			res += A[i][j]*x[j];
		}
		cout << "res :" << res << " b: " << b[i] << endl;
	}

	return 0;
}
