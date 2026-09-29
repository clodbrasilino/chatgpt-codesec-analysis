#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long maxSumBitonicSubsequence(const int arr[], int n) {
    if (n <= 0) {
        return 0;
    }
    if (arr == NULL) {
        return LLONG_MIN;
    }

    long long *inc = calloc((size_t)n, sizeof(long long));
    long long *dec = calloc((size_t)n, sizeof(long long));
    if (inc == NULL || dec == NULL) {
        free(inc);
        free(dec);
        return LLONG_MIN;
    }

    for (int i = 0; i < n; ++i) {
        inc[i] = arr[i];
        for (int j = 0; j < i; ++j) {
            if (arr[j] < arr[i] && inc[j] + arr[i] > inc[i]) {
                inc[i] = inc[j] + arr[i];
            }
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        dec[i] = arr[i];
        for (int j = n - 1; j > i; --j) {
            if (arr[j] < arr[i] && dec[j] + arr[i] > dec[i]) {
                dec[i] = dec[j] + arr[i];
            }
        }
    }

    long long max_sum = LLONG_MIN;
    for (int i = 0; i < n; ++i) {
        long long sum = inc[i] + dec[i] - arr[i];
        if (sum > max_sum) {
            max_sum = sum;
        }
    }

    free(inc);
    free(dec);
    return max_sum;
}

int main(void) {
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    long long result = maxSumBitonicSubsequence(arr, n);
    if (result == LLONG_MIN) {
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return 0;
}