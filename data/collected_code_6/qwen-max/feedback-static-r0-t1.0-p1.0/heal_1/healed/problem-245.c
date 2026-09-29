#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSumBiTonicSubsequence(const int arr[], int n) {
    int i, j, k;
    int *inc, *dec, max_sum = 0;
    
    inc = (int *)malloc(n * sizeof(int));
    dec = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        inc[i] = arr[i];
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[i] > arr[j] && inc[i] < inc[j] + arr[i]) {
                inc[i] = inc[j] + arr[i];
            }
        }
    }

    for (i = n - 1; i >= 0; i--) {
        for (k = n - 1; k > i; k--) {
            if (arr[i] > arr[k] && dec[i] < dec[k] + arr[i]) {
                dec[i] = dec[k] + arr[i];
            }
        }
        if (dec[i] == 0) {
            dec[i] = arr[i];
        }
    }

    for (i = 0; i < n; i++) {
        if (max_sum < (inc[i] + dec[i] - arr[i])) {
            max_sum = inc[i] + dec[i] - arr[i];
        }
    }

    free(inc);
    free(dec);

    return max_sum;
}

int main() {
    const int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findMaxSumBiTonicSubsequence(arr, n);
    printf("%d\n", result);
    return 0;
}