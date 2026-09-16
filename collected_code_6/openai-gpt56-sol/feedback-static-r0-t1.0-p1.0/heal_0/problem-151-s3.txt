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

static int are_coprime(long long first, long long second)
{
    unsigned long long a = first < 0
        ? 0ULL - (unsigned long long)first
        : (unsigned long long)first;
    unsigned long long b = second < 0
        ? 0ULL - (unsigned long long)second
        : (unsigned long long)second;

    return gcd(a, b) == 1U;
}

int main(void)
{
    long long first;
    long long second;

    if (scanf("%lld %lld", &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (are_coprime(first, second)) {
        puts("The numbers are co-prime.");
    } else {
        puts("The numbers are not co-prime.");
    }

    return EXIT_SUCCESS;
}