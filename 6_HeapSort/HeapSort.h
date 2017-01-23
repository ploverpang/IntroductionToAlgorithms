#include <iostream>
#include <vector>

#define MAX_SIZE 100

using namespace std;
class MaxHeap
{
public: 
	MaxHeap(int* array, int array_size);
	MaxHeap();
	void heapSort();
private:
	size_t leftchild_index(size_t n)
	{
		return 2*n;
	}
	size_t righchild_index(size_t n)
	{
		return 2*n + 1;
	}
	size_t parent_index(size_t n)
	{
		return n/2;
	}
	void max_heapify(int* array, size_t k);

/*  data structure  */
	size_t size;
	int elem[MAX_SIZE];
}