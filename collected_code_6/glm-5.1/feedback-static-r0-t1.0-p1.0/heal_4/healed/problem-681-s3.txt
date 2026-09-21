#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

unsigned long smallest_prime_divisor(unsigned long n) {
    if (n <= 1) {
        return 0;
    }
    if (n % 2 == 0) {
        return 2;
    }
    for (unsigned long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return i;
        }
    }
    return n;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t argv_len = strnlen(argv[1], 256);
    if (argv_len == 0) {
        fprintf(stderr, "Invalid input: empty string\n");
        return EXIT_FAILURE;
    }
    if (argv_len == 256 && argv[1][256] != '\0') {
        fprintf(stderr, "Invalid input: string too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (errno == ERANGE || val > ULONG_MAX) {
        fprintf(stderr, "Invalid input: value out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == argv[1] || (size_t)(endptr - argv[1]) != argv_len || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid positive integer\n");
        return EXIT_FAILURE;
    }

    unsigned long result = smallest_prime_divisor(val);
    if (result == 0) {
        printf("No prime divisor for %lu\n", val);
    } else {
        printf("%lu\n", result);
    }

    return EXIT_SUCCESS;
}