#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int minimum_adjacent_swaps(const int *array, size_t length, uint64_t *result)
{
    uint64_t ones = 0;
    uint64_t swaps = 0;

    if (array == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == 1) {
            ++ones;
        } else if (array[i] == 0) {
            if (UINT64_MAX - swaps < ones) {
                return -1;
            }
            swaps += ones;
        } else {
            return -1;
        }
    }

    *result = swaps;
    return 0;
}

int main(void)
{
    size_t length;
    int *array = NULL;
    uint64_t swaps;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        if (length > SIZE_MAX / sizeof(*array)) {
            return EXIT_FAILURE;
        }

        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (scanf("%d", &array[i]) != 1) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    if (minimum_adjacent_swaps(array, length, &swaps) != 0) {
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", swaps);
    free(array);

    return EXIT_SUCCESS;
}