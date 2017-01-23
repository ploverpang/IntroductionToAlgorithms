#include <iostream>
#include <algorithm>
void swap(int A[], int i, int j) {
	int temp = A[i];  
	A[i] = A[j];
	A[j] = temp;
}

int randint(int l, int u)
{
	if(l>u)
		return -1;
	return (l + rand()%(u-l));
}
int partition(int *A, int size, int p, int r)
{
	swap(A, p, randint(p,r));
	int i = p;
	int j = r+1;
	for(;;)
	{
		do
		{
			++i;
		}while(A[i] < A[p] && i < r);
		do
		{
			--j;
		}while(A[j]>A[p]);
		if(i>j)
			break;
		swap(A, i, j);
	}
	swap(A, p, j);
	return j;
}

void quick_sort(int A[], int size, int p, int r) {
	if(p < r) {
		int q = partition(A, size, p, r);
		quick_sort(A, size, p, q-1);
		quick_sort(A, size, q+1, r);     
	}
}

void main() {
	for(int j=0; j!=20; ++j)
	{
		std::cout << rand() << std::endl;
	}
	int A[8] = {2,8,7,1,3,5,6,4};
	//std::sort(A, A+8);
 	char str[2]={'1','2'};
 	quick_sort(A, 8, 0, 7);     
 	for(int i=0; i<8; i++) {
 		printf("%d\n", A[i]);        
 	}
	system("PAUSE");
}