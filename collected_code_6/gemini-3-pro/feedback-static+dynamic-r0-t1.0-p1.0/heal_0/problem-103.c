#include <stdio.h>
#include <stdlib.h>

unsigned long long eulerian(int n, int m) {
    if (n < 0 || m < 0) {
        return 0;
    }
    if (m >= n) {
        if (n == 0 && m == 0) {
            return 1;
        }
        return 0;
    }
    if (m == 0) {
        return 1;
    }

    unsigned long long *dp = (unsigned long long *)calloc((size_t)(m + 1), sizeof(unsigned long long));
    if (!dp) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = m; j > 0; j--) {
            dp[j] = ((unsigned long long)(i - j) * dp[j - 1]) + ((unsigned long long)(j + 1) * dp[j]);
        }
        dp[0] = 1;
    }

    unsigned long long result = dp[m];
    free(dp);

    return result;
}

int main(void) {
    int n = 5;
    int m = 2;
    
    unsigned long long result = eulerian(n, m);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}