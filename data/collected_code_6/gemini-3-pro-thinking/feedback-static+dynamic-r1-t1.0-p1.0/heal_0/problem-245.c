#include <stdio.h>
#include <stdlib.h>

int max_sum_bitonic_subsequence(const int *arr, size_t n, long long *max_sum);

int max_sum_bitonic_subsequence(const int *arr, size_t n, long long *max_sum) {
    if (arr == NULL || max_sum == NULL || n == 0) {
        return -1;
    }

    long long *msis = (long long *)malloc(n * sizeof(long long));
    if (msis == NULL) {
        return -1;
    }

    long long *msds = (long long *)malloc(n * sizeof(long long));
    if (msds == NULL) {
        free(msis);
        return -1;
    }

    for (size_t i = 0; i < n; i++) {
        msis[i] = (long long)arr[i];
        msds[i] = (long long)arr[i];
    }

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            if (arr[i] > arr[j] && msis[i] < msis[j] + (long long)arr[i]) {
                msis[i] = msis[j] + (long long)arr[i];
            }
        }
    }

    if (n > 1) {
        for (size_t i = n - 1; i > 0; i--) {
            size_t idx = i - 1;
            for (size_t j = n - 1; j > idx; j--) {
                if (arr[idx] > arr[j] && msds[idx] < msds[j] + (long long)arr[idx]) {
                    msds[idx] = msds[j] + (long long)arr[idx];
                }
            }
        }
    }

    *max_sum = msis[0] + msds[0] - (long long)arr[0];

    for (size_t i = 1; i < n; i++) {
        long long current_sum = msis[i] + msds[i] - (long long)arr[i];
        if (current_sum > *max_sum) {
            *max_sum = current_sum;
        }
    }

    free(msis);
    free(msds);

    return 0;
}

int main(void) {
    const int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result_sum = 0;

    if (max_sum_bitonic_subsequence(arr, n, &result_sum) == 0) {
        printf("%lld\n", result_sum);
    } else {
        fprintf(stderr, "Error processing the array.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}