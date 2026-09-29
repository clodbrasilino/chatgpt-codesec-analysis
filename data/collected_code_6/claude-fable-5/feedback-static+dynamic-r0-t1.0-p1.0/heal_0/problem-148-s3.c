#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long digit_sum(long long n)
{
    long long sum = 0;

    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}

static long long max_split_digit_sum(long long n)
{
    long long part = 0;
    long long candidate = 9;

    while (candidate <= n) {
        part = candidate;
        if (candidate > (LLONG_MAX - 9) / 10) {
            break;
        }
        candidate = candidate * 10 + 9;
    }

    return digit_sum(part) + digit_sum(n - part);
}

int main(void)
{
    long long n = 0;
    int result;

    printf("Enter a non-negative number: ");

    result = scanf("%lld", &n);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Error: number must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum digit sum: %lld\n", max_split_digit_sum(n));

    return EXIT_SUCCESS;
}