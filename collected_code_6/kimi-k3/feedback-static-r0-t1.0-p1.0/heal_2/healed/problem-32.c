#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long largest_prime_factor(long long n) {
    long long largest = -1;
    long long divisor = 2;

    if (n < 2) {
        return -1;
    }

    while (n % divisor == 0) {
        largest = divisor;
        n /= divisor;
    }

    divisor = 3;
    while (divisor <= n / divisor) {
        while (n % divisor == 0) {
            largest = divisor;
            n /= divisor;
        }
        divisor += 2;
    }

    if (n > 1) {
        largest = n;
    }

    return largest;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t bytes_read;
    char *endptr;
    long long number;
    long long result;

    bytes_read = getline(&input, &input_size, stdin);
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoll(input, &endptr, 10);

    if (endptr == input) {
        fprintf(stderr, "Invalid input: not a number\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Invalid input: number out of range\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (number < 2) {
        fprintf(stderr, "Number must be greater than or equal to 2\n");
        free(input);
        return EXIT_FAILURE;
    }

    result = largest_prime_factor(number);

    if (result == -1) {
        fprintf(stderr, "Could not determine largest prime factor\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    free(input);
    return EXIT_SUCCESS;
}