#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <float.h>

double geometric_series_sum(double first_term, double common_ratio, int terms) {
    if (terms <= 0) {
        return 0.0;
    }
    if (fabs(common_ratio - 1.0) < DBL_EPSILON) {
        return first_term * terms;
    }
    return first_term * (1.0 - pow(common_ratio, terms)) / (1.0 - common_ratio);
}

int main(int argc, const char *argv[]) {
    double first_term, common_ratio, sum;
    long long_val;
    int terms;
    char *endptr;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_ratio> <terms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    first_term = strtod(argv[1], &endptr);
    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Error: Invalid first term.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    common_ratio = strtod(argv[2], &endptr);
    if (endptr == argv[2] || *endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Error: Invalid common ratio.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    long_val = strtol(argv[3], &endptr, 10);
    if (endptr == argv[3] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid number of terms.\n");
        return EXIT_FAILURE;
    }
    if (errno == ERANGE || long_val > INT_MAX || long_val < INT_MIN) {
        fprintf(stderr, "Error: Number of terms out of range.\n");
        return EXIT_FAILURE;
    }
    terms = (int)long_val;

    if (terms <= 0) {
        fprintf(stderr, "Error: Number of terms must be positive.\n");
        return EXIT_FAILURE;
    }

    sum = geometric_series_sum(first_term, common_ratio, terms);
    printf("Sum of geometric series: %.10f\n", sum);

    return EXIT_SUCCESS;
}