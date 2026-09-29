#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static bool can_sort_by_picking_corners(const int array[], size_t length)
{
    if (array == NULL && length != 0U) {
        return false;
    }

    if (length < 2U) {
        return true;
    }

    int *sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    size_t left = 0U;
    size_t right = length - 1U;
    bool possible = true;

    for (size_t i = 0U; i < length; ++i) {
        if (array[left] == sorted[i]) {
            ++left;
        } else if (array[right] == sorted[i]) {
            if (right == 0U) {
                possible = false;
                break;
            }
            --right;
        } else {
            possible = false;
            break;
        }
    }

    free(sorted);
    return possible;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0U; i < length; ++i) {
            if (scanf("%d", &array[i]) != 1) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    puts(can_sort_by_picking_corners(array, length) ? "Yes" : "No");

    free(array);
    return EXIT_SUCCESS;
}