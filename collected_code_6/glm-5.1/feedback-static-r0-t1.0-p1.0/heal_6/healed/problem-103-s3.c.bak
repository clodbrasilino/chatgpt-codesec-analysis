#include <stdio.h>
#include <stdlib.h>

unsigned long long eulerian_number(int n, int m) {
    if (n < 0 || m < 0 || m >= n) {
        return 0;
    }
    if (m == 0) {
        return 1;
    }
    int cols = n + 2;
    unsigned long long *prev = (unsigned long long *)calloc(cols, sizeof(unsigned long long));
    unsigned long long *curr = (unsigned long long *)calloc(cols, sizeof(unsigned long long));
    if (prev == NULL || curr == NULL) {
        fprintf(stderr, "Allocation failed\n");
        free(prev);
        free(curr);
        exit(EXIT_FAILURE);
    }
    prev[0] = 1;
    for (int i = 1; i <= n; i++) {
        curr[0] = 1;
        for (int j = 1; j < i; j++) {
            curr[j] = (unsigned long long)(i - j) * prev[j] + (unsigned long long)(j + 1) * prev[j - 1];
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
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 < 0 || val2 < 0) {
        fprintf(stderr, "n and m must be non-negative integers\n");
        return EXIT_FAILURE;
    }
    int n = (int)val1;
    int m = (int)val2;
    unsigned long long result = eulerian_number(n, m);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}