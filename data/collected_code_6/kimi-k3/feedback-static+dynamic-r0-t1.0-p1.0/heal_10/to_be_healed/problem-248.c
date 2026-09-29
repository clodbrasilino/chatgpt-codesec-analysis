#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define BUFFER_SIZE 256

double harmonic_sum(int n)
{
    double sum = 0.0;
    int i;

    if (n <= 0) {
        return 0.0;
    }

    for (i = 1; i <= n; i++) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *endptr;
    long value;
    double result;

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
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

    while (isspace((unsigned char)*endptr)) {
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
    printf("%.15f\n", result);

    return EXIT_SUCCESS;
}