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

int main(int argc, char *argv[]) {
    double a, r, sum;
    int n;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <ratio> <num_terms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    a = strtod(argv[1], NULL);
    r = strtod(argv[2], NULL);
    n = atoi(argv[3]);

    if (n < 0) {
        fprintf(stderr, "Number of terms must be non-negative.\n");
        return EXIT_FAILURE;
    }

    sum = geometric_series_sum(a, r, n);
    printf("%.6f\n", sum);

    return EXIT_SUCCESS;
}