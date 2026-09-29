#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int first_factorial_digit(unsigned long long number)
{
    if (number < 2ULL) {
        return 1;
    }

    double logarithm = lgamma((double)number + 1.0) / log(10.0);

    if (!isfinite(logarithm)) {
        return -1;
    }

    double fractional_part = logarithm - floor(logarithm);
    int digit = (int)floor(pow(10.0, fractional_part) + 1e-12);

    return digit < 10 ? digit : 1;
}

int main(void)
{
    unsigned long long number;
    char trailing_character;

    errno = 0;

    if (scanf("%llu", &number) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (scanf(" %c", &trailing_character) == 1) {
        fputs("Unexpected trailing input\n", stderr);
        return EXIT_FAILURE;
    }

    int digit = first_factorial_digit(number);

    if (digit < 0) {
        fputs("Unable to calculate the result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}