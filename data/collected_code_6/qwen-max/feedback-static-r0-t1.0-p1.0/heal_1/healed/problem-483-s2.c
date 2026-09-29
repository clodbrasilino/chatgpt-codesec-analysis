#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long factorial(unsigned int n) {
    unsigned long long result = 1;
    for (unsigned int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

unsigned int findFirstDivisibleByX(unsigned int x) {
    unsigned int n = 1;
    while (1) {
        unsigned long long fact = factorial(n);
        if (fact % x == 0) {
            return n;
        }
        ++n;
    }
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <x>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long x = strtoul(argv[1], &endptr, 0);
    if (*endptr != '\0' || x < 2 || (x > UINT_MAX)) {
        fprintf(stderr, "x must be a natural number greater than 1 and within the range of an unsigned integer\n");
        return EXIT_FAILURE;
    }

    unsigned int result = findFirstDivisibleByX((unsigned int)x);
    printf("The first natural number whose factorial is divisible by %lu is %u\n", x, result);

    return EXIT_SUCCESS;
}