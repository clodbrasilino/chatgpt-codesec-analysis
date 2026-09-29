#include <stdio.h>
#include <stdlib.h>

int maxSumIncludingK(const int arr[], size_t n, size_t i, size_t k, long long *result);

int maxSumIncludingK(const int arr[], size_t n, size_t i, size_t k, long long *result)
{
    long long *dp;
    long long best;
    size_t x;
    size_t y;

    if (arr == NULL || result == NULL) {
        return -1;
    }
    if (n == 0U || i >= n || k >= n || k <= i) {
        return -1;
    }

    dp = (long long *)malloc(n * sizeof(long long));
    if (dp == NULL) {
        return -1;
    }

    for (x = 0U; x <= i; x++) {
        if (arr[x] < arr[k]) {
            dp[x] = (long long)arr[x];
        } else {
            dp[x] = 0LL;
        }
        for (y = 0U; y < x; y++) {
            if (arr[y] < arr[x] && arr[x] < arr[k] && dp[y] > 0LL) {
                if (dp[y] + (long long)arr[x] > dp[x]) {
                    dp[x] = dp[y] + (long long)arr[x];
                }
            }
        }
    }

    best = 0LL;
    for (x = 0U; x <= i; x++) {
        if (dp[x] > best) {
            best = dp[x];
        }
    }

    *result = best + (long long)arr[k];
    free(dp);
    return 0;
}

int main(void)
{
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t i = 4U;
    size_t k = 6U;
    long long answer = 0LL;

    if (maxSumIncludingK(arr, n, i, k, &answer) != 0) {
        if (fprintf(stderr, "Error: invalid input or allocation failure\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Maximum sum: %lld\n", answer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}