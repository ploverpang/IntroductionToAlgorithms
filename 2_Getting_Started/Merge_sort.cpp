#include <stdio.h>

void merge(int A[], int p, int q, int r) {
     int n1 = q-p+1; 
     int n2 = r-q;
     
     int L[n1+1];
     int R[n2+1];
     int i, j;
     for(i=0; i<n1; i++) {
             L[i]=A[p+i];
     }
     for(j=0; j<n2; j++) {
              R[j] = A[q+j];
     }
     L[i+1] = 65535;
     R[j+1] = 65535;
     
     // Merge 
     i=0;
     j=0;
     for(int k=p; k<=r; k++) {
             if(L[i] > R[j]) {
                A[k] = R[j];
                j++;
             }
             else {
                 A[k] = L[i];
                 i++;
             }
     }
}

void merge_sort(int A[], int p, int r) {
     if(p<r) {
             int q = (r-p)/2;
             merge_sort(A, p, q);
             merge_sort(A, q+1, r);
             merge(A, p, q, r);
     }
}

int main() {
    int A[10] = {10,4,3,5,1,9,8,7,2,6};
    merge_sort(A, 0, 9);
    for(int i=0; i<10; i++) {
            printf("%d\n", A[i]);
    }
}
