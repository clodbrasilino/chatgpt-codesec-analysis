#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_pairwise_xor(const uint64_t *array, size_t length, uint64_t *result)
{
    if (array == NULL || result == NULL) {
        return -1;
    }

    uint64_t sum = 0;

    for (unsigned int bit = 0; bit < 64U; ++bit) {
        uint64_t ones = 0;

        for (size_t i = 0; i < length; ++i) {
            ones += (array[i] >> bit) & UINT64_C(1);
        }

        uint64_t zeros = (uint64_t)length - ones;
        uint64_t pairs = ones * zeros;

        if (bit == 63U && pairs != 0U) {
            return -1;
        }

        uint64_t contribution = pairs << bit;

        if (UINT64_MAX - sum < contribution) {
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

    if (scanf("%zu", &length) != 1 || length > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t *array = NULL;

    if (length > 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
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

    uint64_t result;
    int status = sum_pairwise_xor(array, length, &result);
    free(array);

    if (status != 0) {
        fputs("Result overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}