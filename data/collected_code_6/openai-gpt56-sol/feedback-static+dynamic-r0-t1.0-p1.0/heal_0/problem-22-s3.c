#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static bool find_first_duplicate(const int *array, size_t length, int *duplicate)
{
    int *sorted;

    if (array == NULL || duplicate == NULL || length < 2U) {
        return false;
    }

    if (length > SIZE_MAX / sizeof(*sorted)) {
        return false;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    for (size_t i = 1U; i < length; ++i) {
        if (sorted[i] == sorted[i - 1U]) {
            const int value = sorted[i];

            for (size_t j = 0U; j < length; ++j) {
                if (array[j] == value) {
                    for (size_t k = j + 1U; k < length; ++k) {
                        if (array[k] == value) {
                            *duplicate = value;
                            free(sorted);
                            return true;
                        }
                    }
                }
            }
        }
    }

    free(sorted);
    return false;
}

int main(void)
{
    const int array[] = {2, 1, 3, 5, 3, 2};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int duplicate;

    if (find_first_duplicate(array, length, &duplicate)) {
        if (printf("%d\n", duplicate) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No duplicate found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}