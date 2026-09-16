#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

static int concatenate_integers(const unsigned int values[], size_t count,
                                uintmax_t *result)
{
    uintmax_t combined = 0;

    if (values == NULL || result == NULL || count == 0) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        uintmax_t value = values[i];
        uintmax_t multiplier = 10;

        for (uintmax_t n = value; n >= 10; n /= 10) {
            if (multiplier > UINTMAX_MAX / 10) {
                return 0;
            }
            multiplier *= 10;
        }

        if (combined > (UINTMAX_MAX - value) / multiplier) {
            return 0;
        }

        combined = combined * multiplier + value;
    }

    *result = combined;
    return 1;
}

int main(void)
{
    const unsigned int values[] = {12U, 34U, 5U, 678U};
    const size_t count = sizeof(values) / sizeof(values[0]);
    uintmax_t result = 0;

    if (!concatenate_integers(values, count, &result)) {
        if (fputs("Conversion failed\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    errno = 0;
    if (printf("%" PRIuMAX "\n", result) < 0 || errno != 0) {
        return 1;
    }

    return 0;
}