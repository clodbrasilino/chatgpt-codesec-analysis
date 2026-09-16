#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

double calculate_harmonic_sum(int n) {
    if (n < 2) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += 1.0 / i;
    }

    return sum;
}

int main(int argc, const char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val < 2 || val > INT_MAX) {
        fprintf(stderr, "Invalid input. Please provide an integer greater than 1.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    double result = calculate_harmonic_sum(n);

    printf("%.6f\n", result);

    return EXIT_SUCCESS;
}