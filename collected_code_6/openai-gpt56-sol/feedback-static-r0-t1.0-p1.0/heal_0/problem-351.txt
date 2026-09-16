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
    size_t length = 0U;
    size_t k = 0U;

    if (scanf("%zu %zu", &length, &k) != 2 || length == 0U || k == 0U) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    int result = 0;
    const bool found = find_first_occurring_k_times(array, length, k, &result);

    if (found) {
        printf("%d\n", result);
    } else {
        printf("No such element\n");
    }

    free(array);
    return EXIT_SUCCESS;
}