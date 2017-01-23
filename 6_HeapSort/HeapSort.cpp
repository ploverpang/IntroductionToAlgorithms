#include <iostream>
#include <Vector>

void max_heapify(int* array);
int parent_index(int n);
int leftchild_index(int n);
int rigthchild_index(int n);
void build_maxheap(int &array[]);
void heap_sort(int &array[]);

int main()
{
}

void max_heapify(int &array[], int root_index)
{
	rc_idx = rightchild_index(root_index);
	lc_idx = leftchild_index(root_index);
	lager_idx = array[rc_idx] > array[lc_idx] ? rc_idx : lc_idx;
	
	if((rc_idx <= array.length) || (lc_idx <= array.length)) // Be sure not exceed array's length
	{
		// If child lager than root, exchange them and max_heapify larger child
		if(array[root_index] < array[lager_idx])
		{
			int temp = array[root_index];
			array[root_index] = array[lager_index];
			array[lager_index] = temp;

			max_heapify(array, lager_idx);
		}
	}
}

void build_maxheap(int &array[], int root_index)
{
	int heap_length = array.length;
	int i = heap_length / 2;
	for(; i >= 1; --i)
	{
		build_maxheap(array, i);
	}
}

void heap_sort(int &array[])
{
	build_maxheap(array, 0);
	for(i=array.length; i >= 1; --i)	
	{
		int temp = array[i];
		array[i] = array[0];
		array[0] = temp;

		
	}
}
int parent_index(int n) 
{
	return n/2;
}

int leftchild_index(int n) 
{
	return 2*n;
}

int rigthchild_index(int n)
{
	return (2*n-1);
}