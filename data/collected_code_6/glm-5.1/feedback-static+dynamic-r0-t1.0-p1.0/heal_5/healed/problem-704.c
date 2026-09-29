#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double harmonic_sum(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / (double)i;
    }
    return sum;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val < 1 || val > INT_MAX) {
        fprintf(stderr, "Invalid input: must be a positive integer within range\n");
        return EXIT_FAILURE;
    }
    double result = harmonic_sum((int)val);
    printf("%.15f\n", result);
    return EXIT_SUCCESS;
}