#include <stdio.h>
#include <stdlib.h>

int longestIncreasingSubsequence(const int *arr, size_t n)
{
    if (arr == NULL || n == 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    size_t i;
    size_t j;
    int maxLength = 1;

    for (i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > maxLength) {
            maxLength = dp[i];
        }
    }

    free(dp);
    dp = NULL;

    return maxLength;
}

int main(void)
{
    int arr[] = {10, 9, 2, 5, 3, 7, 101, 18};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result;

    result = longestIncreasingSubsequence(arr, n);
    if (result < 0) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Length of longest increasing subsequence: %d\n", result);

    return EXIT_SUCCESS;
}