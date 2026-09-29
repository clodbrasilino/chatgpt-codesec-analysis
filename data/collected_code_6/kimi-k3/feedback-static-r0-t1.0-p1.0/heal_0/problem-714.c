#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_distinct_prime_power_factors(unsigned long long n)
{
    int count = 0;
    unsigned long long p;

    if (n < 2ULL) {
        return 0;
    }

    while (n % 2ULL == 0ULL) {
        n /= 2ULL;
    }
    if (n != 1ULL) {
        count++;
    } else {
        count++;
        return count;
    }

    for (p = 3ULL; p <= n / p; p += 2ULL) {
        if (n % p == 0ULL) {
            count++;
            while (n % p == 0ULL) {
                n /= p;
            }
        }
    }

    if (n > 1ULL) {
        count++;
    }

    return count;
}

int main(void)
{
    unsigned long long num;
    int result;

    printf("Enter a positive integer: ");
    if (scanf("%llu", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (num == 0ULL) {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }

    result = count_distinct_prime_power_factors(num);
    printf("Number of distinct prime power factors: %d\n", result);

    return EXIT_SUCCESS;
}