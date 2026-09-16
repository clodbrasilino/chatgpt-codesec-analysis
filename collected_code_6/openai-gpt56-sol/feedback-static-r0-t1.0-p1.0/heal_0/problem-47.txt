#include <stdio.h>
#include <stdlib.h>

static int last_digit_factorial_quotient(unsigned long long a,
                                         unsigned long long b,
                                         int *result)
{
    static const int cycle[] = {6, 2, 4, 8};
    unsigned long long difference;

    if (result == NULL || a > b) {
        return 0;
    }

    difference = b - a;

    if (difference == 0) {
        *result = 1;
    } else if (difference >= 5 || (a < 5 && b >= 5)) {
        *result = 0;
    } else {
        *result = cycle[(b - 1) % 4];
    }

    return 1;
}

int main(void)
{
    unsigned long long a;
    unsigned long long b;
    int last_digit;

    if (scanf("%llu %llu", &a, &b) != 2) {
        return EXIT_FAILURE;
    }

    if (!last_digit_factorial_quotient(a, b, &last_digit)) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", last_digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}