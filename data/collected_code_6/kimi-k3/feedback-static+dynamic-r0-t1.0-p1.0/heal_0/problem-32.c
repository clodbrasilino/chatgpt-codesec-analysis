#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    char input[256];
    char *endptr;
    long long number;
    long long result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    number = strtoll(input, &endptr, 10);

    if (endptr == input) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }

    if (number < 2) {
        fprintf(stderr, "Number must be greater than or equal to 2\n");
        return EXIT_FAILURE;
    }

    result = largest_prime_factor(number);

    if (result == -1) {
        fprintf(stderr, "Could not determine largest prime factor\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}