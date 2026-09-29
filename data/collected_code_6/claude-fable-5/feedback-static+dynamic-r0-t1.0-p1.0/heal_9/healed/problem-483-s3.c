#include <stdio.h>
#include <stdlib.h>

static unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long m)
{
    return (unsigned long long)(((unsigned __int128)a * b) % m);
}

static unsigned long long first_factorial_divisible(unsigned long long x)
{
    unsigned long long remainder;
    unsigned long long n;

    if (x == 0ULL) {
        return 0ULL;
    }

    remainder = 1ULL % x;
    n = 1ULL;
    remainder = mulmod(remainder, n, x);

    while (remainder != 0ULL) {
        n++;
        remainder = mulmod(remainder, n, x);
    }

    return n;
}

int main(void)
{
    unsigned long long x;
    unsigned long long result;
    int scan_status;

    printf("Enter a positive integer: ");
    scan_status = scanf("%llu", &x);

    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (x == 0ULL) {
        fprintf(stderr, "Error: input must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    result = first_factorial_divisible(x);

    if (result == 0ULL) {
        fprintf(stderr, "Error: computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("The first natural number whose factorial is divisible by %llu is %llu\n", x, result);

    return EXIT_SUCCESS;
}