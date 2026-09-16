#include <stdio.h>
#include <stdlib.h>

static unsigned long long smallest_prime_divisor(unsigned long long n)
{
    unsigned long long i;

    if (n < 2ULL) {
        return 0ULL;
    }
    if (n % 2ULL == 0ULL) {
        return 2ULL;
    }
    for (i = 3ULL; i <= n / i; i += 2ULL) {
        if (n % i == 0ULL) {
            return i;
        }
    }
    return n;
}

int main(void)
{
    unsigned long long n;
    unsigned long long result;

    printf("Enter a positive integer: ");
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = smallest_prime_divisor(n);
    if (result == 0ULL) {
        fprintf(stderr, "Number must be greater than 1\n");
        return EXIT_FAILURE;
    }

    printf("Smallest prime divisor of %llu is %llu\n", n, result);
    return EXIT_SUCCESS;
}