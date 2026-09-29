#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c)
{
    int *dp;
    int i;
    int result;

    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return -1;
    }

    dp = malloc((size_t)(n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0; i <= n; i++) {
        dp[i] = -1;
    }
    dp[0] = 0;

    for (i = 0; i <= n; i++) {
        if (dp[i] == -1) {
            continue;
        }
        if (i + a <= n && dp[i + a] < dp[i] + 1) {
            dp[i + a] = dp[i] + 1;
        }
        if (i + b <= n && dp[i + b] < dp[i] + 1) {
            dp[i + b] = dp[i] + 1;
        }
        if (i + c <= n && dp[i + c] < dp[i] + 1) {
            dp[i + c] = dp[i] + 1;
        }
    }

    result = dp[n];
    free(dp);
    return result;
}

int main(void)
{
    int n;
    int a;
    int b;
    int c;
    int result;

    n = 7;
    a = 5;
    b = 2;
    c = 5;

    result = max_segments(n, a, b, c);
    if (result < 0) {
        printf("No valid segmentation possible for n = %d\n", n);
    } else {
        printf("Maximum segments for n = %d: %d\n", n, result);
    }

    n = 17;
    a = 2;
    b = 1;
    c = 3;

    result = max_segments(n, a, b, c);
    if (result < 0) {
        printf("No valid segmentation possible for n = %d\n", n);
    } else {
        printf("Maximum segments for n = %d: %d\n", n, result);
    }

    return EXIT_SUCCESS;
}