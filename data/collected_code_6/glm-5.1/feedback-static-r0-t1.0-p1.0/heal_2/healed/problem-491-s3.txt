#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

double geometric_series_sum(double a, double r, int n) {
    if (n <= 0) {
        return 0.0;
    }
    if (r == 1.0) {
        return a * n;
    }
    return a * (1.0 - pow(r, n)) / (1.0 - r);
}

int main(int argc, char const * const argv[]) {
    double a, r, sum;
    long n_long;
    int n;
    char *endptr;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <ratio> <num_terms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    a = strtod(argv[1], &endptr);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    r = strtod(argv[2], &endptr);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    n_long = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || n_long > INT_MAX || n_long < 0) {
        fprintf(stderr, "Number of terms must be a valid non-negative integer within range.\n");
        return EXIT_FAILURE;
    }
    n = (int)n_long;

    sum = geometric_series_sum(a, r, n);
    printf("%.6f\n", sum);

    return EXIT_SUCCESS;
}