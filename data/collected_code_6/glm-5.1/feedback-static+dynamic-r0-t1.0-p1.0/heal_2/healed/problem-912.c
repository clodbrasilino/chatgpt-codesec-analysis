#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

double ln_lobb_number(int n, int m) {
    if (n <= 0 || m <= 0 || n < m) {
        return NAN;
    }
    double lg_term_1 = lgamma(2 * n + 1) - 2.0 * lgamma(n + 1);
    double lg_term_2 = lgamma(2 * m + 1) - 2.0 * lgamma(m + 1);
    double lg_term_3 = lgamma(2 * (n - m) + 1) - 2.0 * lgamma((n - m) + 1);
    double lg_result = lg_term_1 + lg_term_2 + lg_term_3;
    if (lg_result == HUGE_VAL) {
        return NAN;
    }
    return lg_result;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    char *endptr_n;
    errno = 0;
    long val_n = strtol(argv[1], &endptr_n, 10);
    if (errno != 0 || endptr_n == argv[1] || *endptr_n != '\0' || val_n < INT_MIN || val_n > INT_MAX) {
        return EXIT_FAILURE;
    }
    char *endptr_m;
    errno = 0;
    long val_m = strtol(argv[2], &endptr_m, 10);
    if (errno != 0 || endptr_m == argv[2] || *endptr_m != '\0' || val_m < INT_MIN || val_m > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val_n;
    int m = (int)val_m;
    double result = ln_lobb_number(n, m);
    if (isnan(result)) {
        return EXIT_FAILURE;
    }
    printf("%.15e\n", result);
    return EXIT_SUCCESS;
}