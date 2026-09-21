#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    return value >= 0
        ? (uint64_t)value
        : (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
}

static uint64_t gcd_pair(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;
    char extra;

    if (value == NULL) {
        return -1;
    }

    errno = 0;

    if (scanf("%" SCNuMAX, &parsed) != 1 ||
        errno == ERANGE ||
        parsed == 0 ||
        parsed > SIZE_MAX) {
        return -1;
    }

    if (scanf("%c", &extra) == 1 &&
        extra != ' ' && extra != '\t' && extra != '\n' &&
        extra != '\r' && extra != '\f' && extra != '\v') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    intmax_t parsed;

    if (value == NULL) {
        return -1;
    }

    errno = 0;

    if (scanf("%" SCNdMAX, &parsed) != 1 ||
        errno == ERANGE ||
        parsed < INT64_MIN ||
        parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    size_t count;
    uint64_t result = 0;

    if (read_size(&count) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t value;

        if (read_int64(&value) != 0) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        result = gcd_pair(result, magnitude(value));
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}