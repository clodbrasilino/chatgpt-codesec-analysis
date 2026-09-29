#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static bool find_first_occurring_k_times(const int *array, size_t length,
                                         size_t k, int *result)
{
    if (array == NULL || result == NULL || length == 0U || k == 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        size_t count = 0U;

        for (size_t j = 0U; j < length; ++j) {
            if (array[j] == array[i]) {
                ++count;
            }
        }

        if (count == k) {
            *result = array[i];
            return true;
        }
    }

    return false;
}

int main(void)
{
    int array[] = {1, 7, 4, 3, 4, 8, 7};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const size_t k = 2U;
    int result = 0;

    if (find_first_occurring_k_times(array, length, k, &result)) {
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