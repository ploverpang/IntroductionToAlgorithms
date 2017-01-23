#include <stdio.h>

void insert_sort(int A[]) {
     int array_length = sizeof(A)/sizeof(A[0]);
     printf("The length of array is %d", sizeof(A[0]));
     for(int j=1; j<10; j++) {
             int key = A[j];
             int i = j - 1;
             while((i>=0)  && (A[i]>key)) {
                          A[i+1] = A[i];
                          i = i-1;
             }
             A[i+1] = key;
     }
}

int main() {
    int a[10] = {3,5,4,1,2,6,9,7,8,0};
    insert_sort(a);
    for(int k = 0; k<10; k++) {
          printf("%d", a[k]);
    }
    printf("\n");
}
