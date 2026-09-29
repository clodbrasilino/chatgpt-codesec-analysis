#include <stdio.h>
#include <stdlib.h>

static long long find_min_sum_of_factors(long long n)
{
    long long sum = 0;
    long long divisor = 2;

    if (n < 2) {
        return n;
    }

    while (divisor * divisor <= n) {
        while (n % divisor == 0) {
            sum += divisor;
            n /= divisor;
        }
        divisor++;
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
    int scan_status = 0;

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

    result = find_min_sum_of_factors(number);
    printf("Minimum sum of factors of %lld is %lld\n", number, result);

    return EXIT_SUCCESS;
}