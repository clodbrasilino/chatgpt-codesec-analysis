#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

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

int main(int argc, const char *const argv[]) {
    int n = 5;
    int k = 3;

    if (argc >= 3) {
        char *endptr;
        long n_val;
        long k_val;

        errno = 0;
        n_val = strtol(argv[1], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || n_val < 0 || n_val > 10000) {
            fprintf(stderr, "Invalid input for n.\n");
            return EXIT_FAILURE;
        }
        n = (int)n_val;

        errno = 0;
        k_val = strtol(argv[2], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || k_val < 0 || k_val > n_val) {
            fprintf(stderr, "Invalid input for k.\n");
            return EXIT_FAILURE;
        }
        k = (int)k_val;
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