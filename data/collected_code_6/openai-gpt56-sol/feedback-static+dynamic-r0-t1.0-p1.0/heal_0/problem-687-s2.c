#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    return value < 0 ? (uintmax_t)(-(value + 1)) + 1U : (uintmax_t)value;
}

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    return b == 0U ? a : gcd(b, a % b);
}

int main(void)
{
    intmax_t first;
    intmax_t second;

    if (scanf("%" SCNdMAX " %" SCNdMAX, &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", gcd(magnitude(first), magnitude(second)));
    return EXIT_SUCCESS;
}