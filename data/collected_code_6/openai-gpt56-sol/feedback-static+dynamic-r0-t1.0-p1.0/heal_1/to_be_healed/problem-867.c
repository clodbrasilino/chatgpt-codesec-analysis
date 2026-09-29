#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int minimum_to_make_sum_even(const int64_t *array, size_t length, int64_t *result)
{
    if (array == NULL || result == NULL) {
        return 0;
    }

    unsigned int parity = 0U;

    for (size_t i = 0; i < length; ++i) {
        parity ^= (unsigned int)((uint64_t)array[i] & UINT64_C(1));
    }

    *result = (int64_t)parity;
    return 1;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = NULL;

    if (length > 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            /* Possible weaknesses found:
             * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
             */
            if (scanf("%" SCNd64, &array[i]) != 1) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    } else {
        array = malloc(sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    int64_t minimum;

    if (!minimum_to_make_sum_even(array, length, &minimum)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", minimum) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}