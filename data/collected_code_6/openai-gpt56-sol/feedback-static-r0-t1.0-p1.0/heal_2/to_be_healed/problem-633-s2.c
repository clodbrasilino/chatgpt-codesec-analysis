#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_pairwise_xor(const uint64_t *array, size_t length,
                            uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL || (array == NULL && length != 0)) {
        return -1;
    }

    if (length > UINT64_MAX) {
        return -1;
    }

    for (unsigned int bit = 0; bit < 64U; ++bit) {
        uint64_t ones = 0;

        for (size_t i = 0; i < length; ++i) {
            ones += (array[i] >> bit) & UINT64_C(1);
        }

        uint64_t zeros = (uint64_t)length - ones;

        if (ones != 0 && zeros > UINT64_MAX / ones) {
            return -1;
        }

        uint64_t differing_pairs = ones * zeros;

        if (differing_pairs > (UINT64_MAX >> bit)) {
            return -1;
        }

        uint64_t contribution = differing_pairs << bit;

        if (sum > UINT64_MAX - contribution) {
            return -1;
        }

        sum += contribution;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(uint64_t)) {
        return EXIT_FAILURE;
    }

    uint64_t *array = NULL;

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNu64, &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    uint64_t result;

    if (sum_pairwise_xor(array, length, &result) != 0) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}