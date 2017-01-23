/* 二分查找，递归和非递归两种
	2014.2.12  */

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int binarySearch(int *a, size_t size, int v)
{
	int start = 0;
	int end = size-1;
	int m;
	while(start <= end)
	{
		m = start + (end-start)/2;
		if(a[m] == v)
		{
			//assert(a[m]==v);
			return m;
		}
		if(a[m] < v)
		{
			start = m+1;
		}
		else
		{
			end = m-1;
		}
	}
	return -1;
}

int BSRecursionImplement(int *a, size_t l, size_t u, int v)
{
	if(l>u)
	{
		return -1;
	}
	int m = l + (u-l)/2;
	if(a[m] == v)
		return m;
	if(a[m] > v)
		BSRecursionImplement(a, l, m-1, v);
	else
		BSRecursionImplement(a, m+1, u, v);
}

int binarySearchRecursion(int *a, size_t size, int v)
{
	return BSRecursionImplement(a, 0, size-1, v);
}

/*
int main()
{
	int a[10] = {0,1,2,3,4,5,6,7,8,9};
	int i,j;
	//scanf("%d", &i);
	cin >> i >> j;
	cout << "Find value 2 in array, result should be " << i << " , Result: " << binarySearch(a, 10, i) << endl; 
	cout << "Find value 2 in array, result should be " << j << " ,  Recursion Result: " << binarySearchRecursion(a, 10, j) << endl; 
	system("PAUSE");
	return 0;
}
*/