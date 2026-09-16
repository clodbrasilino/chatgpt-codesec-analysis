#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef bool (*map_function)(uint64_t, size_t, uint64_t *);

static bool checked_multiply(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || (a != 0 && b > UINT64_MAX / a)) {
        return false;
    }

    *result = a * b;
    return true;
}

static bool power_by_index(uint64_t base, size_t index, uint64_t *result)
{
    uint64_t value = 1;
    uint64_t factor = base;
    size_t exponent = index;

    if (result == NULL) {
        return false;
    }

    while (exponent != 0) {
        if ((exponent & 1U) != 0 &&
            !checked_multiply(value, factor, &value)) {
            return false;
        }

        exponent >>= 1U;

        if (exponent != 0 &&
            !checked_multiply(factor, factor, &factor)) {
            return false;
        }
    }

    *result = value;
    return true;
}

static bool map(const uint64_t *input, uint64_t *output, size_t length,
                map_function function)
{
    size_t i;

    if (function == NULL ||
        (length != 0 && (input == NULL || output == NULL))) {
        return false;
    }

    for (i = 0; i < length; ++i) {
        if (!function(input[i], i, &output[i])) {
            return false;
        }
    }

    return true;
}

bool create_power_list(const uint64_t *bases, size_t length,
                       uint64_t **power_list)
{
    uint64_t *result;

    if (power_list == NULL) {
        return false;
    }

    *power_list = NULL;

    if (length == 0) {
        return true;
    }

    if (bases == NULL || length > SIZE_MAX / sizeof(*result)) {
        return false;
    }

    result = malloc(length * sizeof(*result));
    if (result == NULL) {
        return false;
    }

    if (!map(bases, result, length, power_by_index)) {
        free(result);
        return false;
    }

    *power_list = result;
    return true;
}

int main(void)
{
    const uint64_t bases[] = {1, 2, 3, 4, 5};
    const size_t length = sizeof(bases) / sizeof(bases[0]);
    uint64_t *power_list = NULL;
    size_t i;

    if (!create_power_list(bases, length, &power_list)) {
        fputs("Unable to create the power list.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        if (printf("%" PRIu64 "%c", power_list[i],
                   i + 1 == length ? '\n' : ' ') < 0) {
            free(power_list);
            return EXIT_FAILURE;
        }
    }

    free(power_list);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}