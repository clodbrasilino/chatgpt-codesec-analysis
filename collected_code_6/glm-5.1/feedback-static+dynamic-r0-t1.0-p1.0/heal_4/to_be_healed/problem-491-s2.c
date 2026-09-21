#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

double geometric_series_sum(double a, double r, int n) {
    if (n <= 0) {
        return 0.0;
    }
    if (r == 1.0) {
        return a * (double)n;
    }
    return a * (1.0 - pow(r, n)) / (1.0 - r);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_ratio> <number_of_terms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_a;
    char *endptr_r;
    char *endptr_n;

    double a = strtod(argv[1], &endptr_a);
    double r = strtod(argv[2], &endptr_r);
    long n = strtol(argv[3], &endptr_n, 10);

    if (endptr_a == argv[1] || *endptr_a != '\0' ||
        endptr_r == argv[2] || *endptr_r != '\0' ||
        endptr_n == argv[3] || *endptr_n != '\0' ||
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        n <= 0 || n > INT_MAX) {
        fprintf(stderr, "Error: Invalid input. Number of terms must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    double sum = geometric_series_sum(a, r, (int)n);
    printf("%.6f\n", sum);

    return EXIT_SUCCESS;
}