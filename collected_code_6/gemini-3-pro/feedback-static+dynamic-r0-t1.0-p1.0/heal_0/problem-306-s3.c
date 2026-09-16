#include <stdio.h>
#include <stdlib.h>

int maxSumIncreasingSubsequenceWithK(int* arr, int n, int i, int k) {
    if (arr == NULL || n <= 0 || i < 0 || i >= n || k <= i || k >= n) {
        return -1;
    }

    int* msis = (int*)malloc((i + 1) * sizeof(int));
    if (msis == NULL) {
        return -1;
    }

    for (int j = 0; j <= i; j++) {
        msis[j] = arr[j];
    }

    for (int j = 1; j <= i; j++) {
        for (int p = 0; p < j; p++) {
            if (arr[j] > arr[p] && msis[j] < msis[p] + arr[j]) {
                msis[j] = msis[p] + arr[j];
            }
        }
    }

    int max_sum = -1;
    for (int j = 0; j <= i; j++) {
        if (arr[j] < arr[k]) {
            if (max_sum < msis[j] + arr[k]) {
                max_sum = msis[j] + arr[k];
            }
        }
    }

    free(msis);
    return max_sum;
}

int main(void) {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 4;
    int k = 6;

    int result = maxSumIncreasingSubsequenceWithK(arr, n, i, k);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Error or no valid subsequence found.\n");
    }

    return 0;
}