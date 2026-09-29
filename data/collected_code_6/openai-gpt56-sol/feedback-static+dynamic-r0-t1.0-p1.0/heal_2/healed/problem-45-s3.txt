#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    return value < 0
        ? (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1)
        : (uintmax_t)value;
}

static uintmax_t gcd_pair(uintmax_t a, uintmax_t b)
{
    while (b != UINTMAX_C(0)) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_intmax(intmax_t *value)
{
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    char *end;
    errno = 0;
    intmax_t parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    intmax_t count_input;

    if (!read_intmax(&count_input) || count_input <= 0 ||
        (uintmax_t)count_input > SIZE_MAX / sizeof(intmax_t)) {
        fputs("Invalid array size\n", stderr);
        return EXIT_FAILURE;
    }

    size_t count = (size_t)count_input;
    intmax_t *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_intmax(&values[i])) {
            fputs("Invalid array element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    uintmax_t result = UINTMAX_C(0);

    for (size_t i = 0; i < count; ++i) {
        uintmax_t a = result;
        uintmax_t b = magnitude(values[i]);

        while (b != UINTMAX_C(0)) {
            uintmax_t remainder = a % b;
            a = b;
            b = remainder;
        }

        result = a;
    }

    free(values);

    if (printf("%" PRIuMAX "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}