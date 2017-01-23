#include "stdio.h"
//size 是数组长度 
void swap(int A[], int i, int j) {
     int temp = A[i];  
     A[i] = A[j];
     A[j] = temp;
}

int partition(int A[], int size, int p, int r) {
    int i = p-1;
    int x = A[r]; //尾部元素
    for(int j=p; j<r; j++) {
            if(A[j] < x) {
                    i=i+1;
                    swap(A, i, j);
            }
    }
    swap(A, i+1, r);     
    return i+1;
}

void quick_sort(int A[], int size, int p, int r) {
     if(p < r) {
          int q = partition(A, size, p, r);
          quick_sort(A, size, p, q-1);
          quick_sort(A, size, q+1, r);     
     }
}

int main() {
     int A[8] = {2,8,7,1,3,5,6,4};
     quick_sort(A, 8, 0, 7);
     for(int i=0; i<8; i++) {
     printf("%d\n", A[i]);        
     }
}
     
     
