#include "stdio.h"
//ע������A[0]��ͷ,ȡ�Ѷ�Ԫ��Ҳ��ȡ��0�� 
int left(int i) { return 2*i; }
int right(int i) { return 2*i+1;}
int parent(int i) { return i/2; }

int largest; //ע�⣬��largest����Ϊȫ�ֱ���������ÿ�εݹ�������¸�ֵ��ʧȥ�˱Ƚϵ����� 
void max_heapify(int A[], int i, int heap_size) {
     int left_index = left(i);
     int right_index = right(i);
     
     if(left_index < heap_size-1) {
                   if(A[left_index] > A[i])
                                    largest = left_index;
                   else  
                                    largest = i;                    
     }
     if(right_index < heap_size-1){
                    if(A[right_index] > A[largest])
                                      largest = right_index;
     }
     if(largest != i) {
                int temp = A[largest];
                A[largest] = A[i];
                A[i] = temp;
                max_heapify(A, largest, heap_size); 
     }
     
}

void build_maxheap(int A[], int heap_size) {
     for(int i=((heap_size/2)-1); i>=0; i--) {
             max_heapify(A, i, heap_size);        
     }     
}

void heap_sort(int A[], int heap_size) {
     build_maxheap(A, heap_size);
     for(int i=heap_size-1; i>=0; i--) {
             int temp = A[0];
             A[0] = A[i];
             A[i] = temp;
             heap_size = heap_size - 1;
             max_heapify(A, 0, heap_size);
     }
}

int main() {
        int A[10] = {10,4,3,5,1,9,8,7,2,6};
        heap_sort(A, 10);
           for(int i=0; i<10; i++) {
                   printf("%d\n", A[i]);
           }
}
