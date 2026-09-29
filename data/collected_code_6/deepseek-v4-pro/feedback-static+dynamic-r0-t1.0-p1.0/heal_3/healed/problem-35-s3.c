#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <inttypes.h>

#define INPUT_BUFFER_SIZE 64

unsigned long long rectangular_number(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    if (n > INT_MAX / 2 - 1) {
        fprintf(stderr, "Error: n too large, overflow would occur\n");
        exit(EXIT_FAILURE);
    }
    return (unsigned long long)n * (n + 1);
}

int main(void) {
    int n;
    char input[INPUT_BUFFER_SIZE];

    printf("Enter n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    size_t len = strnlen(input, sizeof(input));
    if (len == 0) {
        fprintf(stderr, "Error: Empty input\n");
        return EXIT_FAILURE;
    }

    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Error: Input too long\n");
        return EXIT_FAILURE;
    }

    char *endptr = NULL;
    errno = 0;
    long val = strtol(input, &endptr, 10);

    if (endptr == input) {
        fprintf(stderr, "Error: Invalid integer input\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (*endptr != '\n' && *endptr != ' ' && *endptr != '\t' && *endptr != '\r') {
            fprintf(stderr, "Error: Invalid integer input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Error: Integer out of range\n");
        return EXIT_FAILURE;
    }

    if (val < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        return EXIT_FAILURE;
    }

    n = (int)val;

    unsigned long long result = rectangular_number(n);
    printf("The %d-th rectangular number is %llu\n", n, result);

    return EXIT_SUCCESS;
}