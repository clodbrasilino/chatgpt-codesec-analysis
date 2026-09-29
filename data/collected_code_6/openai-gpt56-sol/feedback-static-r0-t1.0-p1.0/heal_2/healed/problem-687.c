#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static uintmax_t magnitude(intmax_t value)
{
    if (value < 0) {
        return (uintmax_t)(-(value + 1)) + UINTMAX_C(1);
    }

    return (uintmax_t)value;
}

int main(void)
{
    intmax_t first;
    intmax_t second;
    int extra;

    if (scanf("%" SCNdMAX " %" SCNdMAX, &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        extra = getchar();
    } while (extra == ' ' || extra == '\t' || extra == '\n' ||
             extra == '\r' || extra == '\f' || extra == '\v');

    if (extra != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", gcd(magnitude(first), magnitude(second)));

    return EXIT_SUCCESS;
}