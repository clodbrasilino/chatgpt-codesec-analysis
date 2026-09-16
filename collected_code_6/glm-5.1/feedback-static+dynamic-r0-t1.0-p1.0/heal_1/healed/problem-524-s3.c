#include <stdio.h>
#include <stdlib.h>

int maxSumIS(const int arr[], int n) {
    if (n <= 0 || arr == NULL) {
        return 0;
    }
    int *msis = (int *)malloc(n * sizeof(int));
    if (msis == NULL) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        msis[i] = arr[i];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && msis[j] + arr[i] > msis[i]) {
                msis[i] = msis[j] + arr[i];
            }
        }
    }
    int max_sum = msis[0];
    for (int i = 1; i < n; i++) {
        if (msis[i] > max_sum) {
            max_sum = msis[i];
        }
    }
    free(msis);
    return max_sum;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = maxSumIS(arr, n);
    printf("%d\n", result);
    return 0;
}