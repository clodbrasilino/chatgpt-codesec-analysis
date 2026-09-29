#include <stdio.h>
#include <stdlib.h>

static long long largest_prime_factor(long long n)
{
    long long largest = -1;
    long long factor;

    if (n < 2) {
        return -1;
    }

    while (n % 2 == 0) {
        largest = 2;
        n /= 2;
    }

    for (factor = 3; factor <= n / factor; factor += 2) {
        while (n % factor == 0) {
            largest = factor;
            n /= factor;
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

    printf("Enter a number: ");
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = largest_prime_factor(number);
    if (result == -1) {
        fprintf(stderr, "Error: number must be greater than 1\n");
        return EXIT_FAILURE;
    }

    printf("Largest prime factor of %lld is %lld\n", number, result);
    return EXIT_SUCCESS;
}