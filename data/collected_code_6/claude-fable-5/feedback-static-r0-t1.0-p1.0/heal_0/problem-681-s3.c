#include <stdio.h>
#include <stdlib.h>

unsigned long smallest_prime_divisor(unsigned long n)
{
    if (n < 2UL) {
        return 0UL;
    }
    if (n % 2UL == 0UL) {
        return 2UL;
    }
    if (n % 3UL == 0UL) {
        return 3UL;
    }
    for (unsigned long i = 5UL; i <= n / i; i += 6UL) {
        if (n % i == 0UL) {
            return i;
        }
        if (n % (i + 2UL) == 0UL) {
            return i + 2UL;
        }
    }
    return n;
}

int main(void)
{
    unsigned long n = 0UL;
    int result = 0;

    printf("Enter a number: ");
    result = scanf("%lu", &n);
    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long divisor = smallest_prime_divisor(n);
    if (divisor == 0UL) {
        printf("The number %lu has no prime divisors\n", n);
    } else {
        printf("The smallest prime divisor of %lu is %lu\n", n, divisor);
    }

    return EXIT_SUCCESS;
}