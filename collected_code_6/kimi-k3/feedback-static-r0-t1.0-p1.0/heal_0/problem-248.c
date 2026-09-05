#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

double harmonic_sum(int n)
{
    double sum = 0.0;
    int i;

    if (n <= 0) {
        return 0.0;
    }

    for (i = 1; i < n; i++) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

int main(void)
{
    char buffer[256];
    char *endptr;
    long value;
    double result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == buffer) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        return EXIT_FAILURE;
    }

    if (value < 1) {
        fprintf(stderr, "Please enter a positive integer\n");
        return EXIT_FAILURE;
    }

    result = harmonic_sum((int)value);
    printf("Harmonic sum of %ld-1: %.15f\n", value, result);

    return EXIT_SUCCESS;
}