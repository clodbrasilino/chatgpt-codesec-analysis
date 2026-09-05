#include <stdio.h>
#include <stdlib.h>

long long largest_prime_factor(long long n) {
    if (n < 2) {
        return -1;
    }

    long long max_prime = -1;

    while (n % 2 == 0) {
        max_prime = 2;
        n /= 2;
    }

    for (long long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            max_prime = i;
            n /= i;
        }
    }

    if (n > 2) {
        max_prime = n;
    }

    return max_prime;
}

int main(int argc, char * const argv[const]) {
    long long number;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    number = strtoll(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: Not a valid integer\n");
        return EXIT_FAILURE;
    }

    if (number < 2) {
        fprintf(stderr, "Input must be an integer greater than or equal to 2\n");
        return EXIT_FAILURE;
    }

    long long result = largest_prime_factor(number);

    if (result == -1) {
        fprintf(stderr, "No prime factor found\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}