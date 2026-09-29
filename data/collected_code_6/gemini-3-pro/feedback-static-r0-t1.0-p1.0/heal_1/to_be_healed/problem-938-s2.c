#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'B' can be declared as const array [constParameter]
 *  Parameter 'C' can be declared as const array [constParameter]
 *  Parameter 'A' can be declared as const array [constParameter]
 */
void findClosest(int A[], int B[], int C[], int p, int q, int r) {
    int diff = INT_MAX;
    int res_i = 0, res_j = 0, res_k = 0;
    int i = 0, j = 0, k = 0;

    if (p <= 0 || q <= 0 || r <= 0) {
        return;
    }

    while (i < p && j < q && k < r) {
        int minimum = A[i];
        if (B[j] < minimum) minimum = B[j];
        if (C[k] < minimum) minimum = C[k];

        int maximum = A[i];
        if (B[j] > maximum) maximum = B[j];
        if (C[k] > maximum) maximum = C[k];

        if (maximum - minimum < diff) {
            res_i = i;
            res_j = j;
            res_k = k;
            diff = maximum - minimum;
        }

        if (diff == 0) break;

        if (A[i] == minimum) i++;
        else if (B[j] == minimum) j++;
        else k++;
    }

    printf("%d, %d, %d\n", A[res_i], B[res_j], C[res_k]);
}

int main(void) {
    int A[] = {1, 4, 10, 15};
    int B[] = {2, 11, 20, 24};
    int C[] = {2, 9, 14, 25};

    int p = sizeof(A) / sizeof(A[0]);
    int q = sizeof(B) / sizeof(B[0]);
    int r = sizeof(C) / sizeof(C[0]);

    findClosest(A, B, C, p, q, r);

    return 0;
}