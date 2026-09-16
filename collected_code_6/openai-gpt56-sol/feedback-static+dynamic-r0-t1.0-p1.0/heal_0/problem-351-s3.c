#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int value;
    size_t count;
} Frequency;

static int find_first_element_occurring_k_times(
    const int *array,
    size_t length,
    size_t k,
    int *result
) {
    Frequency *frequencies;
    size_t unique_count = 0U;

    if (array == NULL || result == NULL || length == 0U || k == 0U) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*frequencies)) {
        return 0;
    }

    frequencies = calloc(length, sizeof(*frequencies));
    if (frequencies == NULL) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        size_t j;

        for (j = 0U; j < unique_count; ++j) {
            if (frequencies[j].value == array[i]) {
                ++frequencies[j].count;
                break;
            }
        }

        if (j == unique_count) {
            frequencies[unique_count].value = array[i];
            frequencies[unique_count].count = 1U;
            ++unique_count;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        for (size_t j = 0U; j < unique_count; ++j) {
            if (frequencies[j].value == array[i] &&
                frequencies[j].count == k) {
                *result = array[i];
                free(frequencies);
                return 1;
            }
        }
    }

    free(frequencies);
    return 0;
}

int main(void) {
    const int array[] = {1, 7, 4, 3, 4, 8, 7, 7, 4};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const size_t k = 3U;
    int result;

    if (find_first_element_occurring_k_times(array, length, k, &result)) {
        if (printf("%d\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No element occurs exactly %zu times.\n", k) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}