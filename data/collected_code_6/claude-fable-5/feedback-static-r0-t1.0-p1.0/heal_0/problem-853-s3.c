#include <stdio.h>
#include <stdlib.h>

long long sum_odd_factors(long long n);

long long sum_odd_factors(long long n)
{
    if (n <= 0) {
        return 0;
    }

    while (n % 2 == 0) {
        n /= 2;
    }

    long long result = 1;

    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            long long term = 1;
            long long power = 1;
            while (n % i == 0) {
                n /= i;
                power *= i;
                term += power;
            }
            result *= term;
        }
    }

    if (n > 1) {
        result *= (1 + n);
    }

    return result;
}

int main(void)
{
    long long number = 0;

    printf("Enter a positive integer: ");

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number <= 0) {
        fprintf(stderr, "Error: number must be positive.\n");
        return EXIT_FAILURE;
    }

    long long sum = sum_odd_factors(number);

    printf("Sum of odd factors of %lld is %lld\n", number, sum);

    return EXIT_SUCCESS;
}