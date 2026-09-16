#include <stdio.h>
#include <stdlib.h>

double find_median_of_trapezium(double a, double b) {
    return (a + b) / 2.0;
}

int main(int argc, char * const argv[]) {
    double a, b, median;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base1> <base2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for base1\n");
        return EXIT_FAILURE;
    }

    if (sscanf(argv[2], "%lf", &b) != 1) {
        fprintf(stderr, "Invalid input for base2\n");
        return EXIT_FAILURE;
    }

    if (a < 0.0 || b < 0.0) {
        fprintf(stderr, "Bases must be non-negative\n");
        return EXIT_FAILURE;
    }

    median = find_median_of_trapezium(a, b);
    printf("%.6f\n", median);

    return EXIT_SUCCESS;
}