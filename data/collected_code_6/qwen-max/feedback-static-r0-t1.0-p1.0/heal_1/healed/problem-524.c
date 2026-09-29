#include <stdio.h>
#include <limits.h>

int max_sum_increasing_subsequence(const int *arr, int n) {
    int msis[n];
    int i, j, max = 0;
    for (i = 0; i < n; i++)
        msis[i] = arr[i];
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[i] > arr[j] && msis[i] < msis[j] + arr[i]) {
                msis[i] = msis[j] + arr[i];
            }
        }
    }
    for (i = 0; i < n; i++) {
        if (max < msis[i])
            max = msis[i];
    }
    return max;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum sum of increasing subsequence: %d\n", max_sum_increasing_subsequence(arr, n));
    return 0;
}