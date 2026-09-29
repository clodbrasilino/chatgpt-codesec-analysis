#include <stdio.h>
#include <stdlib.h>

long long smallest_prime_divisor(long long n)
{
    long long i;

    if (n < 2) {
        return -1;
    }
    if (n % 2 == 0) {
        return 2;
    }
    for (i = 3; i <= n / i; i += 2) {
        if (n % i == 0) {
            return i;
        }
    }
    return n;
}

int main(void)
{
    long long n;
    long long result;
    int status;

    printf("Enter a number: ");
    status = scanf("%lld", &n);
    if (status != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 2) {
        fprintf(stderr, "Number must be greater than or equal to 2\n");
        return EXIT_FAILURE;
    }

    result = smallest_prime_divisor(n);
    if (result < 0) {
        fprintf(stderr, "No prime divisor found\n");
        return EXIT_FAILURE;
    }

    printf("Smallest prime divisor of %lld is %lld\n", n, result);
    return EXIT_SUCCESS;
}