#include <stdio.h>
#include <stdlib.h>

static long long sum_prime_divisors(long long n)
{
    long long sum = 0;
    long long d = 2;

    if (n < 0) {
        n = -n;
    }

    if (n < 2) {
        return 0;
    }

    while (d * d <= n) {
        if (n % d == 0) {
            sum += d;
            while (n % d == 0) {
                n /= d;
            }
        }
        d++;
    }

    if (n > 1) {
        sum += n;
    }

    return sum;
}

int main(void)
{
    long long number = 0;
    long long result = 0;

    printf("Enter a number: ");

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = sum_prime_divisors(number);

    printf("Sum of prime divisors of %lld is %lld\n", number, result);

    return EXIT_SUCCESS;
}