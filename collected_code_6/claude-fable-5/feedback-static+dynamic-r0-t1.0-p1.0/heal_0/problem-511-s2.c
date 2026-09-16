#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long min_sum_of_factors(long long n)
{
    long long sum = 0;
    long long divisor = 2;

    if (n < 1) {
        return -1;
    }

    if (n == 1) {
        return 1;
    }

    while (divisor * divisor <= n) {
        while (n % divisor == 0) {
            if (sum > LLONG_MAX - divisor) {
                return -1;
            }
            sum += divisor;
            n /= divisor;
        }
        divisor++;
    }

    if (n > 1) {
        if (sum > LLONG_MAX - n) {
            return -1;
        }
        sum += n;
    }

    return sum;
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

    if (number < 1) {
        fprintf(stderr, "Error: input must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    result = min_sum_of_factors(number);
    if (result < 0) {
        fprintf(stderr, "Error: computation failed due to overflow or invalid value.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum sum of factors of %lld is %lld\n", number, result);

    return EXIT_SUCCESS;
}