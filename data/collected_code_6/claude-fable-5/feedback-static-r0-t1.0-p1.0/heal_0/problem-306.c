#include <stdio.h>
#include <stdlib.h>

int maxSumIncludingK(const int *arr, size_t n, size_t i, size_t k, long long *result)
{
    long long *dp = NULL;
    long long best;
    size_t x;
    size_t y;

    if (arr == NULL || result == NULL) {
        return -1;
    }
    if (n == 0U || i >= n || k >= n || k <= i) {
        return -1;
    }

    dp = malloc(n * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (x = 0U; x <= i; x++) {
        dp[x] = (long long)arr[x];
        for (y = 0U; y < x; y++) {
            if (arr[y] < arr[x] && dp[y] + (long long)arr[x] > dp[x]) {
                dp[x] = dp[y] + (long long)arr[x];
            }
        }
    }

    best = (long long)arr[k];
    for (x = 0U; x <= i; x++) {
        if (arr[x] < arr[k] && dp[x] + (long long)arr[k] > best) {
            best = dp[x] + (long long)arr[k];
        }
    }

    free(dp);
    *result = best;
    return 0;
}

int main(void)
{
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t i = 4U;
    size_t k = 6U;
    long long result = 0;

    if (maxSumIncludingK(arr, n, i, k, &result) != 0) {
        (void)fprintf(stderr, "Error: invalid input parameters\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum sum: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}