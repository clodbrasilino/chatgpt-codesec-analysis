#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_pairwise_xor(const uint64_t *array, size_t length, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL || (length != 0 && array == NULL)) {
        return 0;
    }

    for (unsigned int bit = 0; bit < 64U; ++bit) {
        size_t ones = 0;

        for (size_t i = 0; i < length; ++i) {
            ones += (size_t)((array[i] >> bit) & UINT64_C(1));
        }

        size_t zeros = length - ones;

        if (ones != 0 && zeros > UINT64_MAX / ones) {
            return 0;
        }

        uint64_t differing_pairs = (uint64_t)ones * (uint64_t)zeros;

        if (bit == 63U) {
            if (differing_pairs != 0) {
                return 0;
            }
        } else {
            if (differing_pairs > (UINT64_MAX >> bit)) {
                return 0;
            }

            uint64_t contribution = differing_pairs << bit;

            if (sum > UINT64_MAX - contribution) {
                return 0;
            }

            sum += contribution;
        }
    }

    *result = sum;
    return 1;
}

int main(void)
{
    size_t length = 0;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t *array = NULL;

    if (length != 0) {
        array = malloc(length * sizeof(*array));

        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            /* Possible weaknesses found:
             * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
             */
            if (scanf("%" SCNu64, &array[i]) != 1) {
                fputs("Invalid input\n", stderr);
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    uint64_t result = 0;

    if (!sum_pairwise_xor(array, length, &result)) {
        fputs("Result overflow\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(array);

    return EXIT_SUCCESS;
}