#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int* calcBitonicValues(int arr[], int n, int *maxSum) {
    int *L = (int*)malloc(n * sizeof(int));
    int *R = (int*)malloc(n * sizeof(int));

    L[0] = arr[0];
    for (int i = 1; i < n; i++) {
        L[i] = arr[i];
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && L[i] < L[j] + arr[i]) {
                L[i] = L[j] + arr[i];
            }
        }
    }

    R[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        R[i] = arr[i];
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j] && R[i] < R[j] + arr[i]) {
                R[i] = R[j] + arr[i];
            }
        }
    }

    *maxSum = 0;
    for (int i = 0; i < n; i++) {
        *maxSum = max(*maxSum, L[i] + R[i] - arr[i]);
    }

    free(L);
    free(R);
}

int main() {
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxSum;

    calcBitonicValues(arr, n, &maxSum);

    printf("Maximum sum of bi-tonic sub-sequence: %d\n", maxSum);

    return 0;
}