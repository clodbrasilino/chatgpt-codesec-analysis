#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSumBiTonicSubsequence(const int arr[], int n) {
    int *inc = (int *)malloc(n * sizeof(int));
    int *dec = (int *)malloc(n * sizeof(int));

    if (inc == NULL || dec == NULL) {
        free(inc);
        free(dec);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        inc[i] = arr[i];
        dec[i] = arr[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && inc[i] < inc[j] + arr[i]) {
                inc[i] = inc[j] + arr[i];
            }
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && dec[i] < dec[j] + arr[i]) {
                dec[i] = dec[j] + arr[i];
            }
        }
    }

    int max_sum = 0;
    for (int i = 0; i < n; i++) {
        max_sum = max(max_sum, inc[i] + dec[i] - arr[i]);
    }

    free(inc);
    free(dec);
    return max_sum;
}

int main() {
    const int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findMaxSumBiTonicSubsequence(arr, n);
    printf("Maximum sum of bi-tonic sub-sequence: %d\n", result);
    return 0;
}