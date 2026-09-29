#include <stdio.h>
#include <stdlib.h>

static int max2(int a, int b) {
    return (a > b) ? a : b;
}

static int max3(int a, int b, int c) {
    return max2(max2(a, b), c);
}

int maxSumNoThreeConsecutive(const int *arr, size_t n, int *result) {
    if (!arr || !result) {
        return -1;
    }

    if (n == 0) {
        *result = 0;
        return 0;
    }
    if (n == 1) {
        *result = arr[0];
        return 0;
    }
    if (n == 2) {
        *result = arr[0] + arr[1];
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (!dp) {
        return -1;
    }

    dp[0] = arr[0];
    dp[1] = arr[0] + arr[1];
    dp[2] = max3(dp[1], dp[0] + arr[2], arr[1] + arr[2]);

    for (size_t i = 3; i < n; i++) {
        dp[i] = max3(dp[i - 1],
                     dp[i - 2] + arr[i],
                     dp[i - 3] + arr[i] + arr[i - 1]);
    }

    *result = dp[n - 1];
    free(dp);

    return 0;
}

int main(void) {
    int arr[] = {100, 1000, 100, 1000, 1};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int max_sum = 0;

    if (maxSumNoThreeConsecutive(arr, n, &max_sum) == 0) {
        printf("%d\n", max_sum);
    } else {
        fprintf(stderr, "Error calculating maximum sum\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}