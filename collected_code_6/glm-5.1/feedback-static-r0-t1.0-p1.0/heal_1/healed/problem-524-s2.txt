#include <stdio.h>
#include <stdlib.h>

int maxIncreasingSubsequenceSum(const int *arr, int n) {
    if (n <= 0) {
        return 0;
    }

    int *ms = (int *)malloc(n * sizeof(int));
    if (ms == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        ms[i] = arr[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (ms[j] + arr[i] > ms[i]) {
                    ms[i] = ms[j] + arr[i];
                }
            }
        }
    }

    int max_sum = ms[0];
    for (int i = 1; i < n; i++) {
        if (ms[i] > max_sum) {
            max_sum = ms[i];
        }
    }

    free(ms);
    return max_sum;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = maxIncreasingSubsequenceSum(arr, n);
    printf("%d\n", result);

    return 0;
}