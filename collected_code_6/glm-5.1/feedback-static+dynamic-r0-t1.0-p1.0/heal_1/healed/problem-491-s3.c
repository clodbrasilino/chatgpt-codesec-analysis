#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double geometric_series_sum(double a, double r, int n) {
    if (n <= 0) {
        return 0.0;
    }
    if (r == 1.0) {
        return a * n;
    }
    return a * (1.0 - pow(r, n)) / (1.0 - r);
}

int main(int argc, char * const argv[]) {
    double a, r, sum;
    long n;
    char *endptr_a, *endptr_r, *endptr_n;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <ratio> <num_terms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    a = strtod(argv[1], &endptr_a);
    if (*endptr_a != '\0') {
        fprintf(stderr, "Invalid first term.\n");
        return EXIT_FAILURE;
    }

    r = strtod(argv[2], &endptr_r);
    if (*endptr_r != '\0') {
        fprintf(stderr, "Invalid ratio.\n");
        return EXIT_FAILURE;
    }

    n = strtol(argv[3], &endptr_n, 10);
    if (*endptr_n != '\0' || n < 0 || n > 1000000) {
        fprintf(stderr, "Number of terms must be a non-negative integer within safe limits.\n");
        return EXIT_FAILURE;
    }

    sum = geometric_series_sum(a, r, (int)n);
    printf("%.6f\n", sum);

    return EXIT_SUCCESS;
}