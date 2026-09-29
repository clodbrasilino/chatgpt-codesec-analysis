#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t gcd_recursive(uintmax_t a, uintmax_t b)
{
    return b == 0 ? a : gcd_recursive(b, a % b);
}

static uintmax_t magnitude(intmax_t value)
{
    return value < 0
        ? (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1)
        : (uintmax_t)value;
}

int main(void)
{
    char input[256];
    char extra;
    intmax_t first;
    intmax_t second;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(input, "%" SCNdMAX " %" SCNdMAX " %c",
               &first, &second, &extra) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n",
           gcd_recursive(magnitude(first), magnitude(second)));

    return EXIT_SUCCESS;
}