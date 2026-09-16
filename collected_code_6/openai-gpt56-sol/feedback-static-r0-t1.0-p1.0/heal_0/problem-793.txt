#include <stdio.h>
#include <stdlib.h>

static int find_last_position(const int *array, size_t length, int target, size_t *position)
{
    size_t left = 0;
    size_t right = length;

    if (position == NULL || (array == NULL && length != 0)) {
        return 0;
    }

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (array[middle] <= target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    if (left == 0 || array[left - 1] != target) {
        return 0;
    }

    *position = left - 1;
    return 1;
}

int main(void)
{
    int array[] = {1, 2, 2, 2, 3, 4, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const int target = 2;
    size_t position = 0;

    if (find_last_position(array, length, target, &position)) {
        if (printf("%zu\n", position) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Element not found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}