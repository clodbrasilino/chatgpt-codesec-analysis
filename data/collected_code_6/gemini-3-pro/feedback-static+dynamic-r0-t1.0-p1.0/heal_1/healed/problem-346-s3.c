#include <stdio.h>
#include <stdlib.h>

unsigned long long entringer(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }

    unsigned long long *dp = (unsigned long long *)calloc((size_t)(n + 1) * (size_t)(n + 1), sizeof(unsigned long long));
    if (dp == NULL) {
        return 0;
    }

    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        dp[i * (n + 1) + 0] = 0;
        for (int j = 1; j <= i; j++) {
            dp[i * (n + 1) + j] = dp[i * (n + 1) + (j - 1)] + dp[(i - 1) * (n + 1) + (i - j)];
        }
    }

    unsigned long long result = dp[n * (n + 1) + k];
    free(dp);

    return result;
}

int main(int argc, char *argv[]) {
    int n = 5;
    int k = 3;

    if (argc >= 3) {
        n = atoi(argv[1]);
        k = atoi(argv[2]);
    }

    unsigned long long result = entringer(n, k);
    
    if (result > 0 || (n == 0 && k == 0)) {
        printf("%llu\n", result);
    } else {
        fprintf(stderr, "Calculation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}