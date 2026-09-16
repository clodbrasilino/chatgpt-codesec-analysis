#include <stdio.h>
#include <stdlib.h>

static long long largest_prime_factor(long long n)
{
    long long largest = -1;
    long long i;

    if (n < 2) {
        return -1;
    }

    while (n % 2 == 0) {
        largest = 2;
        n /= 2;
    }

    for (i = 3; i <= n / i; i += 2) {
        while (n % i == 0) {
            largest = i;
            n /= i;
        }
    }

    if (n > 1) {
        largest = n;
    }

    return largest;
}

int main(void)
{
    long long number;
    long long result;
    int scan_status;

    printf("Enter a positive integer: ");
    scan_status = scanf("%lld", &number);

    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number < 2) {
        fprintf(stderr, "Error: number must be greater than 1.\n");
        return EXIT_FAILURE;
    }

    result = largest_prime_factor(number);

    if (result < 0) {
        fprintf(stderr, "Error: no prime factor found.\n");
        return EXIT_FAILURE;
    }

    printf("Largest prime factor of %lld is %lld\n", number, result);

    return EXIT_SUCCESS;
}