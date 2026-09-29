#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef bool (*MapFunction)(uint64_t, uint32_t, uint64_t *);

static bool checked_multiply(uint64_t left, uint64_t right, uint64_t *result)
{
    if (result == NULL || (left != 0U && right > UINT64_MAX / left)) {
        return false;
    }

    *result = left * right;
    return true;
}

static bool power_value(uint64_t base, uint32_t exponent, uint64_t *result)
{
    uint64_t value = 1U;
    uint64_t factor = base;

    if (result == NULL) {
        return false;
    }

    while (exponent != 0U) {
        if ((exponent & 1U) != 0U &&
            !checked_multiply(value, factor, &value)) {
            return false;
        }

        exponent >>= 1U;

        if (exponent != 0U &&
            !checked_multiply(factor, factor, &factor)) {
            return false;
        }
    }

    *result = value;
    return true;
}

static bool map(const uint64_t *bases, const uint32_t *indices,
                uint64_t *results, size_t count, MapFunction function)
{
    size_t i;

    if (function == NULL || results == NULL ||
        (count != 0U && (bases == NULL || indices == NULL))) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        if (!function(bases[i], indices[i], &results[i])) {
            return false;
        }
    }

    return true;
}

bool create_power_list(const uint64_t *bases, const uint32_t *indices,
                       size_t count, uint64_t **list)
{
    uint64_t *result;

    if (list == NULL) {
        return false;
    }

    *list = NULL;

    if (count == 0U) {
        return true;
    }

    if (bases == NULL || indices == NULL ||
        count > SIZE_MAX / sizeof(*result)) {
        return false;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return false;
    }

    if (!map(bases, indices, result, count, power_value)) {
        free(result);
        return false;
    }

    *list = result;
    return true;
}

int main(void)
{
    const uint64_t bases[] = {10U, 20U, 30U, 40U, 50U};
    const uint32_t indices[] = {1U, 2U, 3U, 4U, 5U};
    const size_t count = sizeof(bases) / sizeof(bases[0]);
    uint64_t *powers = NULL;
    size_t i;

    if (count != sizeof(indices) / sizeof(indices[0]) ||
        !create_power_list(bases, indices, count, &powers)) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (printf("%" PRIu64 "%c", powers[i],
                   i + 1U == count ? '\n' : ' ') < 0) {
            free(powers);
            return EXIT_FAILURE;
        }
    }

    free(powers);
    return EXIT_SUCCESS;
}