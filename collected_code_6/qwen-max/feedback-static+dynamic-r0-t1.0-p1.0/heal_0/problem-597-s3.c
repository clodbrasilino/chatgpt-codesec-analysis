#include <stdio.h>
#include <stdlib.h>

int findKth(int* A, int m, int* B, int n, int k) {
    if (m > n) return findKth(B, n, A, m, k);
    if (m == 0) return B[k-1];
    if (k == 1) return A[0] < B[0] ? A[0] : B[0];

    int i = (m < k/2) ? m : k/2;
    int j = k - i;

    if (A[i-1] < B[j-1]) {
        return findKth(A + i, m - i, B, n, k - i);
    } else if (B[j-1] < A[i-1]) {
        return findKth(A, m, B + j, n - j, k - j);
    } else {
        return A[i-1];
    }
}

int main() {
    int A[] = {2, 3, 6, 7, 9};
    int B[] = {1, 4, 8, 10};
    int m = sizeof(A) / sizeof(A[0]);
    int n = sizeof(B) / sizeof(B[0]);
    int k = 5;
    
    printf("%d\n", findKth(A, m, B, n, k));
    
    return 0;
}