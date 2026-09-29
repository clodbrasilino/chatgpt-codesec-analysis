#include <stdio.h>
#include <stdlib.h>

static int longest_subsequence_diff_one(const int *arr, size_t n)
{
    size_t i;
    size_t j;
    int result;
    int *dp;

    if (arr == NULL || n == 0U) {
        return 0;
    }

    dp = malloc(n * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0U; i < n; i++) {
        dp[i] = 1;
    }

    result = 1;

    for (i = 1U; i < n; i++) {
        for (j = 0U; j < i; j++) {
            if ((arr[i] == arr[j] + 1) || (arr[i] == arr[j] - 1)) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > result) {
            result = dp[i];
        }
    }

    free(dp);
    return result;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 3, 2};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int length;

    length = longest_subsequence_diff_one(arr, n);
    if (length < 0) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Longest subsequence length: %d\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}