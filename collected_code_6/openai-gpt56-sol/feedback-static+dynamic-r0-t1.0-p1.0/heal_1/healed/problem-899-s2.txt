#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static bool can_be_sorted_by_picking_corners(const int *array, size_t length)
{
    if (length == 0) {
        return true;
    }

    if (array == NULL) {
        return false;
    }

    size_t left = 0;
    size_t right = length;
    int previous = 0;
    bool has_previous = false;

    while (left < right) {
        int selected;

        if (array[left] <= array[right - 1]) {
            selected = array[left++];
        } else {
            selected = array[--right];
        }

        if (has_previous && selected < previous) {
            return false;
        }

        previous = selected;
        has_previous = true;
    }

    return true;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length == 0) {
        puts("YES");
        return EXIT_SUCCESS;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    bool sortable = can_be_sorted_by_picking_corners(array, length);
    puts(sortable ? "YES" : "NO");

    free(array);
    return EXIT_SUCCESS;
}