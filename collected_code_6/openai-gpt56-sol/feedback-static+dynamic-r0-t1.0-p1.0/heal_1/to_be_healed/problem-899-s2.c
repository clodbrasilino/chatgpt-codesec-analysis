#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static bool can_be_sorted_by_picking_corners(const int *array, size_t length)
{
    size_t left = 0;
    size_t right = length;
    bool has_previous = false;
    int previous = 0;

    while (left < right) {
        int selected;

        /* Possible weaknesses found:
         *  Possible null pointer dereference: array [nullPointer]
         *  Null pointer dereference
         */
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

    if (length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assignment 'array=NULL', assigned value is 0
     */
    int *array = NULL;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (length > 0) {
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

    /* Possible weaknesses found:
     *  Calling function 'can_be_sorted_by_picking_corners', 1st argument 'array' value is 0
     */
    bool sortable = can_be_sorted_by_picking_corners(array, length);
    printf("%s\n", sortable ? "YES" : "NO");

    free(array);
    return EXIT_SUCCESS;
}