#include <stdio.h>
#include <stdlib.h>

static int last_digit_of_factorial_quotient(unsigned long long a,
                                            unsigned long long b,
                                            int *result)
{
    static const int factorial_last_digit[] = {1, 1, 2, 6, 4};

    if (result == NULL || a > b) {
        return 0;
    }

    if (b - a >= 5 || (a < 5 && b >= 5)) {
        *result = 0;
        return 1;
    }

    int digit = 1;
    for (unsigned long long value = a + 1; value <= b; ++value) {
        digit = (digit * (int)(value % 10)) % 10;
    }

    *result = digit;
    return 1;
}

int main(void)
{
    unsigned long long a;
    unsigned long long b;
    int result;

    if (scanf("%llu %llu", &a, &b) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!last_digit_of_factorial_quotient(a, b, &result)) {
        fputs("Expected nonnegative integers with a <= b\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}