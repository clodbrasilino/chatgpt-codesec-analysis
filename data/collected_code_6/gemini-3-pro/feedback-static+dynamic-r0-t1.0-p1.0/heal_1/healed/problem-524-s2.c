#include <stdio.h>
#include <stdlib.h>

int maxSumIS(const int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int *msis = (int *)malloc(n * sizeof(int));
    if (msis == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        msis[i] = arr[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && msis[i] < msis[j] + arr[i]) {
                msis[i] = msis[j] + arr[i];
            }
        }
    }

    int max = msis[0];
    for (int i = 1; i < n; i++) {
        if (msis[i] > max) {
            max = msis[i];
        }
    }

    free(msis);

    return max;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = maxSumIS(arr, n);
    if (result != -1) {
        printf("Sum of maximum sum increasing subsequence is %d\n", result);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}