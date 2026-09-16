#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

double harmonic_sum(int n) {
    double sum = 0.0;
    for (int i = n; i >= 1; i--) {
        sum += 1.0 / i;
    }
    return sum;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long n = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || n < 1 || n > INT_MAX) {
        fprintf(stderr, "Invalid input: must be a positive integer\n");
        return EXIT_FAILURE;
    }

    double result = harmonic_sum((int)n);
    printf("%.17g\n", result);

    return EXIT_SUCCESS;
}