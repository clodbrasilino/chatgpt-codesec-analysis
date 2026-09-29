#include <stdio.h>
#include <stdlib.h>

int max(const int a, const int b) {
    return (a > b) ? a : b;
}

int* createArray(int n) {
    return (int*)malloc(n * sizeof(int));
}

void freeArray(int* arr) {
    free(arr);
}

int findMaxSumBiTonicSubsequence(const int arr[], int n) {
    int* inc = createArray(n);
    int* dec = createArray(n);

    if (n == 0) {
        freeArray(inc);
        freeArray(dec);
        return 0;
    }

    inc[0] = arr[0];
    for (int i = 1; i < n; i++) {
        inc[i] = arr[i];
        for (int j = 0; j < i; j++)
            if (arr[i] > arr[j] && inc[i] < inc[j] + arr[i])
                inc[i] = inc[j] + arr[i];
    }

    dec[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--) {
        dec[i] = arr[i];
        for (int j = n-1; j > i; j--)
            if (arr[i] > arr[j] && dec[i] < dec[j] + arr[i])
                dec[i] = dec[j] + arr[i];
    }

    int maxSum = 0;
    for (int i = 0; i < n; i++)
        maxSum = max(maxSum, inc[i] + dec[i] - arr[i]);

    freeArray(inc);
    freeArray(dec);

    return maxSum;
}

int main() {
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findMaxSumBiTonicSubsequence(arr, n);
    printf("Maximum sum of bi-tonic sub-sequence: %d\n", result);
    return 0;
}