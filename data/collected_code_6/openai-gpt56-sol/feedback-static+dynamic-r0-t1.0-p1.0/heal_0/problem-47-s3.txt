#include <stdio.h>
#include <stdlib.h>

static int last_digit_factorial_quotient(unsigned long long a,
                                         unsigned long long b,
                                         int *result)
{
    if (result == NULL || a > b) {
        return 0;
    }

    if (b - a >= 5ULL) {
        *result = 0;
        return 1;
    }

    unsigned int digit = 1U;

    for (unsigned long long value = a + 1ULL; value <= b; ++value) {
        digit = (digit * (unsigned int)(value % 10ULL)) % 10U;
    }

    *result = (int)digit;
    return 1;
}

int main(void)
{
    unsigned long long a = 0ULL;
    unsigned long long b = 0ULL;
    int result = 0;

    if (scanf("%llu %llu", &a, &b) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!last_digit_factorial_quotient(a, b, &result)) {
        fputs("Expected 0 <= a <= b\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}