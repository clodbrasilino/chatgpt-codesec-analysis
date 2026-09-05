#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long cube_sum_odd(int n) {
    if (n < 0) {
        return 0;
    }

    if ((unsigned long long)n * 2 > ULLONG_MAX / n) {
        return 0;
    }

    unsigned long long n_sq = (unsigned long long)n * n;

    if (n_sq > ULLONG_MAX / (2 * n_sq - 1)) {
        return 0;
    }

    return n_sq * (2 * n_sq - 1);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    int n;

    if (argc != 2) {
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return 1;
    }

    n = (int)val;
    unsigned long long result = cube_sum_odd(n);

    printf("%llu\n", result);

    return 0;
}