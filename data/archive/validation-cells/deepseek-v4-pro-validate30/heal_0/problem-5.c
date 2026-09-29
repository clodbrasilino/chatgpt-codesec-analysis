#include <stdio.h>
#include <stdlib.h>

long long count_domino_tilings(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (n % 2 != 0) return 0;

    long long *dp = (long long*)calloc(n + 1, sizeof(long long));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }

    dp[0] = 1;
    dp[2] = 3;

    for (int i = 4; i <= n; i += 2) {
        dp[i] = 4 * dp[i - 2] - dp[i - 4];
    }

    long long result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    int n;
    while (scanf("%d", &n) == 1) {
        if (n < 0) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
        printf("%lld\n", count_domino_tilings(n));
    }
    return EXIT_SUCCESS;
}