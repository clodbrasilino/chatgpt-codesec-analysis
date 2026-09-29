#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long eulerian_number(unsigned int n, unsigned int m) {
    if (m >= n) {
        return 0;
    }
    if (m == 0) {
        return 1;
    }
    size_t rows = (size_t)n + 1;
    size_t cols = rows;
    unsigned long long *dp = (unsigned long long *)malloc(rows * cols * sizeof(unsigned long long));
    if (dp == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            dp[i * cols + j] = 0;
        }
    }
    dp[0] = 1;
    for (size_t i = 1; i <= n; i++) {
        dp[i * cols] = 1;
        for (size_t j = 1; j < i; j++) {
            dp[i * cols + j] = (i - j) * dp[(i - 1) * cols + j] + (j + 1) * dp[(i - 1) * cols + j - 1];
        }
    }
    unsigned long long result = dp[n * cols + m];
    free(dp);
    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1;
    char *endptr2;
    errno = 0;
    unsigned long n_ul = strtoul(argv[1], &endptr1, 10);
    unsigned long m_ul = strtoul(argv[2], &endptr2, 10);
    if (errno != 0 || *endptr1 != '\0' || *endptr2 != '\0' || n_ul > UINT_MAX || m_ul > UINT_MAX) {
        fprintf(stderr, "n and m must be valid non-negative integers\n");
        return EXIT_FAILURE;
    }
    unsigned int n = (unsigned int)n_ul;
    unsigned int m = (unsigned int)m_ul;
    unsigned long long result = eulerian_number(n, m);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}