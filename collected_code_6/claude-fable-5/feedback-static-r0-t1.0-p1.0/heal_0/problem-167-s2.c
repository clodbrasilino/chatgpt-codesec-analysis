#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

static int smallest_power_of_two(unsigned long n, unsigned long *result)
{
    unsigned long power = 1UL;

    if (result == NULL) {
        return -1;
    }

    if (n > (ULONG_MAX >> 1) + 1UL) {
        return -1;
    }

    while (power < n) {
        power <<= 1;
    }

    *result = power;
    return 0;
}

int main(int argc, char *argv[])
{
    unsigned long n;
    unsigned long result;
    char *endptr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoul(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (strchr(argv[1], '-') != NULL) {
        fprintf(stderr, "Negative input not allowed: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (smallest_power_of_two(n, &result) != 0) {
        fprintf(stderr, "Result would overflow for input: %lu\n", n);
        return EXIT_FAILURE;
    }

    printf("%lu\n", result);
    return EXIT_SUCCESS;
}