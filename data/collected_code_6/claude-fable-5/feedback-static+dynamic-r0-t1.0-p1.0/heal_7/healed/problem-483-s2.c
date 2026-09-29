#include <stdio.h>
#include <stdlib.h>

static unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long m)
{
    return (unsigned long long)(((unsigned __int128)a * (unsigned __int128)b) % (unsigned __int128)m);
}

unsigned long long first_factorial_divisible(unsigned long long x)
{
    unsigned long long remainder;
    unsigned long long i;

    if (x == 1ULL) {
        return 1ULL;
    }

    remainder = 1ULL;
    for (i = 2ULL; ; i++) {
        remainder = mulmod(remainder, i, x);
        if (remainder == 0ULL) {
            return i;
        }
    }
}

int main(int argc, const char *argv[])
{
    unsigned long long x;

    if (argc > 1) {
        char *endptr = NULL;
        x = strtoull(argv[1], &endptr, 10);
        if (endptr == argv[1] || (endptr != NULL && *endptr != '\0')) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        if (scanf("%llu", &x) != 1) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }

    if (x == 0ULL) {
        fprintf(stderr, "Input must be a positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", first_factorial_divisible(x));

    return EXIT_SUCCESS;
}