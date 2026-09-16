#include <stdio.h>
#include <stdlib.h>

static long long sum_of_divisors(long long n)
{
    long long sum = 0;
    long long i;

    if (n <= 0) {
        return 0;
    }

    for (i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }

    return sum;
}

int main(void)
{
    long long number;
    long long result;

    printf("Enter a positive integer: ");

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number <= 0) {
        fprintf(stderr, "Error: number must be positive.\n");
        return EXIT_FAILURE;
    }

    if (number > 3000000000000000000LL) {
        fprintf(stderr, "Error: number too large.\n");
        return EXIT_FAILURE;
    }

    result = sum_of_divisors(number);

    printf("Sum of divisors of %lld is %lld\n", number, result);

    return EXIT_SUCCESS;
}