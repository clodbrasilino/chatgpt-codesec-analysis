#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long jacobsthal_lucas(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0 || n == 1) {
        return 2 * (n + 1) - n;
    }
    unsigned long long a = 2;
    unsigned long long b = 2;
    for (int i = 2; i <= n; i++) {
        unsigned long long c = b + 2 * a;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    unsigned long long result = jacobsthal_lucas(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}