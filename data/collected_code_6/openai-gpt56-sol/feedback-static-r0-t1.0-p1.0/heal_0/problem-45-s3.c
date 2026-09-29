#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    return value < 0 ? (uintmax_t)(-(value + 1)) + 1U : (uintmax_t)value;
}

static uintmax_t gcd_pair(uintmax_t a, uintmax_t b)
{
    while (b != 0U) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static uintmax_t gcd_array(const intmax_t values[], size_t count)
{
    uintmax_t result = 0U;

    for (size_t i = 0U; i < count; ++i) {
        result = gcd_pair(result, magnitude(values[i]));
    }

    return result;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(intmax_t)) {
        fputs("Invalid array size\n", stderr);
        return EXIT_FAILURE;
    }

    intmax_t *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%" SCNdMAX, &values[i]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    uintmax_t result = gcd_array(values, count);
    free(values);

    if (printf("%" PRIuMAX "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}