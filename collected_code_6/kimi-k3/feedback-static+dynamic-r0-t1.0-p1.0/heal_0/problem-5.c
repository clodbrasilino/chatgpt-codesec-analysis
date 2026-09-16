#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t count_domino_tilings(int n) {
    if (n < 0) {
        return 0;
    }
    if (n % 2 != 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }

    int m = n / 2;
    uint64_t *dp = (uint64_t *)calloc((size_t)m + 1, sizeof(uint64_t));
    if (dp == NULL) {
        return 0;
    }

    dp[0] = 1;
    if (m >= 1) {
        dp[1] = 3;
    }

    for (int i = 2; i <= m; i++) {
        dp[i] = 4 * dp[i - 1] - dp[i - 2];
    }

    uint64_t result = dp[m];
    free(dp);
    dp = NULL;

    return result;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    uint64_t result = count_domino_tilings(n);
    printf("%llu\n", (unsigned long long)result);

    return EXIT_SUCCESS;
}