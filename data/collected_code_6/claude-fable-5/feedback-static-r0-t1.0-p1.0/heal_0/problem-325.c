#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int min_squares(int n)
{
    int *dp;
    int i;
    int j;
    int result;

    if (n < 0) {
        return -1;
    }

    if (n == 0) {
        return 0;
    }

    dp = malloc(((size_t)n + 1U) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;
    for (i = 1; i <= n; i++) {
        dp[i] = INT_MAX;
        for (j = 1; (long long)j * j <= (long long)i; j++) {
            int candidate = dp[i - (j * j)];
            if (candidate != INT_MAX && (candidate + 1) < dp[i]) {
                dp[i] = candidate + 1;
            }
        }
    }

    result = dp[n];
    free(dp);
    return result;
}

int main(void)
{
    int n;
    int result;

    printf("Enter a non-negative integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }

    result = min_squares(n);
    if (result < 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of squares for %d is %d\n", n, result);
    return EXIT_SUCCESS;
}