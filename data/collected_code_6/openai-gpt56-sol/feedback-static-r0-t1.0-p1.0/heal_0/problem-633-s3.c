#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_pairwise_xor(const uint64_t *array, size_t length, uint64_t *result)
{
    uint64_t sum = 0;

    if (array == NULL || result == NULL) {
        return 0;
    }

    for (unsigned int bit = 0; bit < 63U; ++bit) {
        size_t ones = 0;

        for (size_t i = 0; i < length; ++i) {
            ones += (size_t)((array[i] >> bit) & UINT64_C(1));
        }

        if (ones != 0U && length - ones > UINT64_MAX / ones) {
            return 0;
        }

        uint64_t differing_pairs = (uint64_t)ones * (uint64_t)(length - ones);

        if (differing_pairs > (UINT64_MAX >> bit)) {
            return 0;
        }

        uint64_t contribution = differing_pairs << bit;

        if (sum > UINT64_MAX - contribution) {
            return 0;
        }

        sum += contribution;
    }

    size_t sign_bit_ones = 0;

    for (size_t i = 0; i < length; ++i) {
        sign_bit_ones += (size_t)(array[i] >> 63U);
    }

    if (sign_bit_ones != 0U && length != sign_bit_ones) {
        return 0;
    }

    *result = sum;
    return 1;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t *array = NULL;

    if (length > 0U) {
        array = malloc(length * sizeof(*array));

        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (scanf("%" SCNu64, &array[i]) != 1) {
                fputs("Invalid input\n", stderr);
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    uint64_t result;

    if (!sum_pairwise_xor(array, length, &result)) {
        fputs("Result overflow\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}