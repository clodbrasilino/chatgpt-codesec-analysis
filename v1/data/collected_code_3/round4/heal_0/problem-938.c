#include <stdio.h>
#include <limits.h>

void findClosest(int A[], int B[], int C[], int p, int q, int r, int *res1, int *res2, int *res3) {
    int diff = INT_MAX;
    int i = 0, j = 0, k = 0;

    while (i < p && j < q && k < r) {
        int minimum = min(A[i], min(B[j], C[k]));
        int maximum = max(A[i], max(B[j], C[k]));

        if (maximum - minimum < diff) {
            *res1 = A[i];
            *res2 = B[j];
            *res3 = C[k];
            diff = maximum - minimum;
        }

        if (diff == 0) break;

        if (A[i] == minimum) i++;
        else if (B[j] == minimum) j++;
        else k++;
    }
}

int min(int x, int y) {
    return (x < y) ? x : y;
}

int max(int x, int y) {
    return (x > y) ? x : y;
}

int main() {
    int A[] = {1, 4, 10};
    int B[] = {2, 15, 20};
    int C[] = {10, 12};

    int p = sizeof(A) / sizeof(A[0]);
    int q = sizeof(B) / sizeof(B[0]);
    int r = sizeof(C) / sizeof(C[0]);

    int res1, res2, res3;

    findClosest(A, B, C, p, q, r, &res1, &res2, &res3);

    printf("Closest elements are %d, %d, %d", res1, res2, res3);
    return 0;
}