#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static bool can_sort_by_picking_corners(const int *array, size_t length)
{
    int *sorted;
    size_t left = 0U;
    size_t right;
    size_t i;

    if (array == NULL && length != 0U) {
        return false;
    }

    if (length < 2U) {
        return true;
    }

    if (length > SIZE_MAX / sizeof(*sorted)) {
        return false;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (i = 0U; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);
    right = length - 1U;

    for (i = 0U; i < length; ++i) {
        if (left <= right && array[left] == sorted[i]) {
            ++left;
        } else if (left <= right && array[right] == sorted[i]) {
            if (right == 0U) {
                free(sorted);
                return i + 1U == length;
            }
            --right;
        } else {
            free(sorted);
            return false;
        }
    }

    free(sorted);
    return true;
}

int main(void)
{
    size_t length;
    int *array = NULL;
    size_t i;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    puts(can_sort_by_picking_corners(array, length) ? "Yes" : "No");

    free(array);
    return EXIT_SUCCESS;
}