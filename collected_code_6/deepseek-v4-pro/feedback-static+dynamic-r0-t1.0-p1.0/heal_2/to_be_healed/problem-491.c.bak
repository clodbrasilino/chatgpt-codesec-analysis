#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    double first_term, common_ratio, sum;
    int terms;
    char *endptr;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_ratio> <terms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    first_term = strtod(argv[1], &endptr);
    if (errno != 0 || *endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid first term.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    common_ratio = strtod(argv[2], &endptr);
    if (errno != 0 || *endptr != '\0' || endptr == argv[2]) {
        fprintf(stderr, "Error: Invalid common ratio.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    long temp_terms = strtol(argv[3], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || endptr == argv[3] || temp_terms <= 0 || temp_terms > 1000000) {
        fprintf(stderr, "Error: Invalid number of terms. Must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    terms = (int)temp_terms;

    sum = geometric_series_sum(first_term, common_ratio, terms);
    printf("Sum of geometric series: %.10f\n", sum);

    return EXIT_SUCCESS;
}