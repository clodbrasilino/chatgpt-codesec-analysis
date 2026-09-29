#include <stdio.h>
#include <limits.h>

int min(int x, int y, int z);
int max(int x, int y, int z);

void findClosest(int A[], int B[], int C[], int p, int q, int r) {
    int diff = INT_MAX;
    int res_i = 0, res_j = 0, res_k = 0;
    int i=0,j=0,k=0;
    while (i < p && j < q && k < r) {
        int minimum = min(A[i], min(B[j], C[k]));
        int maximum = max(A[i], max(B[j], C[k]));
        if (maximum-minimum < diff) {
            res_i = i, res_j = j, res_k = k;
            diff = maximum - minimum;
        }
        if (diff == 0) break;
        if (A[i] == minimum) i++;
        else if (B[j] == minimum) j++;
        else k++;
    }
    printf("Closest elements are %d, %d, %d", A[res_i], B[res_j], C[res_k]);
}

int min(int x, int y, int z) {
    if (x < y) return (x < z)? x : z;
    else return (y < z)? y : z;
}

int max(int x, int y, int z) {
    if (x > y) return (x > z)? x : z;
    else return (y > z)? y : z;
}

int main() {
    int A[] = {1, 4, 10};
    int B[] = {2, 15, 20};
    int C[] = {10, 12};
    int p = sizeof(A) / sizeof(A[0]);
    int q = sizeof(B) / sizeof(B[0]);
    int r = sizeof(C) / sizeof(C[0]);
    findClosest(A, B, C, p, q, r);
    return 0;
}