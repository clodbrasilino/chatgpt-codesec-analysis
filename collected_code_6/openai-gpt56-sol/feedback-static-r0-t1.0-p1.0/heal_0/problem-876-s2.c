#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    while (b != 0U) {
        unsigned long long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm(unsigned long long a, unsigned long long b,
               unsigned long long *result)
{
    unsigned long long divisor;

    if (a == 0U || b == 0U || result == NULL) {
        return -1;
    }

    divisor = gcd(a, b);

    if (a / divisor > ULLONG_MAX / b) {
        return -1;
    }

    *result = (a / divisor) * b;
    return 0;
}

int main(void)
{
    unsigned long long a;
    unsigned long long b;
    unsigned long long result;

    if (scanf("%llu %llu", &a, &b) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (a == 0U || b == 0U) {
        fputs("Inputs must be positive integers\n", stderr);
        return EXIT_FAILURE;
    }

    if (lcm(a, b, &result) != 0) {
        fputs("LCM overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}