#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

double ln_lobb_number(int n, int m) {
    if (n <= 0 || m <= 0 || n < m) {
        return NAN;
    }
    double num_1 = lgamma(2 * n + 1);
    double term_1 = num_1 - 2.0 * lgamma(n + 1);
    double num_2 = lgamma(2 * m + 1);
    double term_2 = num_2 - 2.0 * lgamma(m + 1);
    double num_3 = lgamma(2 * (n - m) + 1);
    double term_3 = num_3 - 2.0 * lgamma((n - m) + 1);
    double log_result = term_1 + term_2 + term_3;
    if (isnan(log_result) || isinf(log_result)) {
        return NAN;
    }
    return log_result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * argv[const]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    char *endptr_n;
    errno = 0;
    long val_n = strtol(argv[1], &endptr_n, 10);
    if (errno != 0 || endptr_n == argv[1] || *endptr_n != '\0' || val_n < INT_MIN || val_n > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val_n;
    char *endptr_m;
    errno = 0;
    long val_m = strtol(argv[2], &endptr_m, 10);
    if (errno != 0 || endptr_m == argv[2] || *endptr_m != '\0' || val_m < INT_MIN || val_m > INT_MAX) {
        return EXIT_FAILURE;
    }
    int m = (int)val_m;
    double result = ln_lobb_number(n, m);
    if (isnan(result)) {
        return EXIT_FAILURE;
    }
    printf("%.15e\n", result);
    return EXIT_SUCCESS;
}