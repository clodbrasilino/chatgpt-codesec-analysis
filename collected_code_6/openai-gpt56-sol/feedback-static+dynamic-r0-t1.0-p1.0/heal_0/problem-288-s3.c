#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_prime(uint64_t p)
{
    uint64_t divisor;

    if (p < 2U) {
        return 0;
    }

    if ((p % 2U) == 0U) {
        return p == 2U;
    }

    for (divisor = 3U; divisor <= p / divisor; divisor += 2U) {
        if ((p % divisor) == 0U) {
            return 0;
        }
    }

    return 1;
}

static size_t count_self_inverse_elements(const int64_t array[],
                                          size_t length,
                                          uint64_t p)
{
    size_t count = 0U;
    size_t i;

    for (i = 0U; i < length; ++i) {
        uint64_t residue;

        if (array[i] >= 0) {
            residue = (uint64_t)array[i] % p;
        } else {
            uint64_t magnitude = (uint64_t)(-(array[i] + 1)) + 1U;
            uint64_t remainder = magnitude % p;
            residue = remainder == 0U ? 0U : p - remainder;
        }

        if (residue == 1U || residue == p - 1U) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    uint64_t p;
    size_t i;
    size_t count;

    if (scanf("%zu %" SCNu64, &length, &p) != 2) {
        return EXIT_FAILURE;
    }

    if (!is_prime(p) || length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    count = count_self_inverse_elements(array, length, p);

    if (printf("%zu\n", count) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}