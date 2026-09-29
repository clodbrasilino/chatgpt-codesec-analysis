#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int count_digits(long long n)
{
    int count = 1;

    if (n < 0) {
        if (n == LLONG_MIN) {
            n = LLONG_MAX;
        } else {
            n = -n;
        }
    }

    while (n >= 10) {
        n /= 10;
        count++;
    }

    return count;
}

static int same_digit_count(long long a, long long b)
{
    return count_digits(a) == count_digits(b);
}

int main(void)
{
    long long a;
    long long b;

    printf("Enter first number: ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%lld", &b) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (same_digit_count(a, b)) {
        printf("The numbers have the same number of digits.\n");
    } else {
        printf("The numbers do not have the same number of digits.\n");
    }

    return EXIT_SUCCESS;
}