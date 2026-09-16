#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static int max_sum_disjoint_pairs(const int *arr, size_t n, int k, long long *result)
{
    int *sorted;
    long long *dp;
    size_t i;

    if (arr == NULL || result == NULL) {
        return -1;
    }

    if (n == 0) {
        *result = 0;
        return 0;
    }

    sorted = malloc(n * sizeof(*sorted));
    if (sorted == NULL) {
        return -1;
    }

    dp = malloc(n * sizeof(*dp));
    if (dp == NULL) {
        free(sorted);
        return -1;
    }

    for (i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, n, sizeof(*sorted), compare_ints);

    dp[0] = 0;
    for (i = 1; i < n; i++) {
        dp[i] = dp[i - 1];
        if ((long long)sorted[i] - (long long)sorted[i - 1] < (long long)k) {
            long long candidate;

            candidate = (long long)sorted[i] + (long long)sorted[i - 1];
            if (i >= 2) {
                candidate += dp[i - 2];
            }
            if (candidate > dp[i]) {
                dp[i] = candidate;
            }
        }
    }

    *result = dp[n - 1];

    free(sorted);
    free(dp);

    return 0;
}

int main(void)
{
    int arr[] = {3, 5, 10, 15, 17, 12, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    long long result = 0;

    if (max_sum_disjoint_pairs(arr, n, k, &result) != 0) {
        fprintf(stderr, "Error computing maximum sum of disjoint pairs\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum sum of disjoint pairs: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}