#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long eulerian_number(int n, int m) {
    if (n < 0 || m < 0 || m >= n) {
        return 0;
    }
    if (m == 0) {
        return 1;
    }
    int size = n + 1;
    unsigned long long *dp = (unsigned long long *)malloc((size_t)size * size * sizeof(unsigned long long));
    if (dp == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == 0) {
                dp[i * size + j] = 1;
            } else {
                dp[i * size + j] = 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            dp[i * size + j] = (unsigned long long)(i - j) * dp[(i - 1) * size + j - 1] + (unsigned long long)(j + 1) * dp[(i - 1) * size + j];
        }
    }
    unsigned long long result = dp[n * size + m];
    free(dp);
    return result;
}

int main(int argc, char const * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1;
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno != 0 || endptr1 == argv[1] || *endptr1 != '\0' || val1 < 0 || val1 > INT_MAX) {
        fprintf(stderr, "n must be a valid non-negative integer\n");
        return EXIT_FAILURE;
    }
    char *endptr2;
    errno = 0;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || endptr2 == argv[2] || *endptr2 != '\0' || val2 < 0 || val2 > INT_MAX) {
        fprintf(stderr, "m must be a valid non-negative integer\n");
        return EXIT_FAILURE;
    }
    int n = (int)val1;
    int m = (int)val2;
    unsigned long long result = eulerian_number(n, m);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}