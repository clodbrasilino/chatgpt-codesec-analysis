#include <stdio.h>
#include <stdlib.h>

unsigned long long eulerian_number(int n, int m) {
    if (n == 0 && m == 0) {
        return 1;
    }
    if (n <= 0 || m < 0 || m >= n) {
        return 0;
    }

    unsigned long long *dp = (unsigned long long *)calloc((size_t)(n + 1), sizeof(unsigned long long));
    if (dp == NULL) {
        return 0;
    }

    dp[0] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = i - 1; j > 0; j--) {
            dp[j] = (unsigned long long)(i - j) * dp[j - 1] + (unsigned long long)(j + 1) * dp[j];
        }
    }

    unsigned long long result = dp[m];
    free(dp);

    return result;
}

int main(void) {
    int n = 5;
    int m = 2;

    unsigned long long result = eulerian_number(n, m);
    
    printf("%llu\n", result);

    return 0;
}