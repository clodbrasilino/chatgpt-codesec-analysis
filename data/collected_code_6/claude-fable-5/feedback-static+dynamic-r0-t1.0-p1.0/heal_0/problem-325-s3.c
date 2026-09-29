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

    dp = malloc(((size_t)n + 1U) * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;
    for (i = 1; i <= n; i++) {
        dp[i] = INT_MAX;
        for (j = 1; (long)j * (long)j <= (long)i; j++) {
            int candidate = dp[i - (j * j)];
            if (candidate != INT_MAX && candidate + 1 < dp[i]) {
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
    int number;
    int answer;

    printf("Enter a non-negative integer: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number < 0) {
        fprintf(stderr, "Number must be non-negative.\n");
        return EXIT_FAILURE;
    }

    answer = min_squares(number);
    if (answer < 0) {
        fprintf(stderr, "Computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of squares summing to %d: %d\n", number, answer);
    return EXIT_SUCCESS;
}