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
    size_t cols = (size_t)n + 1;
    unsigned long long *prev = (unsigned long long *)malloc(cols * sizeof(unsigned long long));
    unsigned long long *curr = (unsigned long long *)malloc(cols * sizeof(unsigned long long));
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (size_t j = 0; j < cols; j++) {
        prev[j] = 0;
        curr[j] = 0;
    }
    prev[0] = 1;
    for (size_t i = 1; i <= n; i++) {
        curr[0] = 1;
        for (size_t j = 1; j < i; j++) {
            curr[j] = (i - j) * prev[j] + (j + 1) * prev[j - 1];
        }
        unsigned long long *temp = prev;
        prev = curr;
        curr = temp;
    }
    unsigned long long result = prev[m];
    free(prev);
    free(curr);
    return result;
}

int main(int argc, char const * const argv[]) {
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