#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double geometric_series_sum(double a, double r, int n) {
    if (n <= 0) {
        return 0.0;
    }
    if (r == 1.0) {
        return a * (double)n;
    }
    return a * (1.0 - pow(r, n)) / (1.0 - r);
}

int main(int argc, char * const argv[]) {
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
        n <= 0) {
        fprintf(stderr, "Error: Invalid input. Number of terms must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    double sum = geometric_series_sum(a, r, (int)n);
    printf("%.6f\n", sum);

    return EXIT_SUCCESS;
}