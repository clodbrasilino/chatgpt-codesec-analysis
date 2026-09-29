#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int* calculateSubsequences(int arr[], int n, int (*calc)(int, int)) {
    int *msis = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        msis[i] = arr[i];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (calc(arr[i], arr[j]) && msis[i] < msis[j] + arr[i]) {
                msis[i] = msis[j] + arr[i];
            }
        }
    }
    return msis;
}

int biTonicSubSeqSum(int arr[], int n) {
    int *inc = calculateSubsequences(arr, n, &max);
    int *dec = calculateSubsequences(arr, n, &min);

    int maxSum = inc[0] + dec[0] - arr[0];
    for (int i = 1; i < n; ++i) {
        maxSum = max(maxSum, inc[i] + dec[i] - arr[i]);
    }

    free(inc);
    free(dec);

    return maxSum;
}

int main() {
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Maximum sum of bi-tonic sub-sequence: %d\n", biTonicSubSeqSum(arr, n));

    return 0;
}