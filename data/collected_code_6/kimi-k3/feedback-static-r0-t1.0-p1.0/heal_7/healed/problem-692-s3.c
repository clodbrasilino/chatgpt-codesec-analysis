#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int last_two_digits_factorial(int n, int *result) {
    int i;
    int value;

    if (result == NULL || n < 0) {
        return -1;
    }

    if (n >= 100) {
        *result = 0;
        return 0;
    }

    value = 1;
    for (i = 2; i <= n; i++) {
        value = (value * i) % 100;
    }

    *result = value;
    return 0;
}

int main(void) {
    char input[64];
    char *endptr;
    long parsed;
    int number;
    int result;
    int status;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }

    len = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        len++;
    }

    if (len == sizeof(input)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input || parsed < 0 || parsed > 1000) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (parsed > INT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    number = (int)parsed;
    status = last_two_digits_factorial(number, &result);

    if (status != 0) {
        fprintf(stderr, "Computation error\n");
        return EXIT_FAILURE;
    }

    printf("%02d\n", result);
    return EXIT_SUCCESS;
}