#include <stdio.h>
#include <stdlib.h>

static int find_first_position(const int *array, size_t length, int target, size_t *position)
{
    size_t left = 0;
    size_t right = length;

    if (array == NULL || position == NULL) {
        return 0;
    }

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (array[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    if (left < length && array[left] == target) {
        *position = left;
        return 1;
    }

    return 0;
}

int main(void)
{
    int array[] = {1, 2, 2, 2, 3, 4, 5};
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t position = 0;
    int target = 2;

    if (find_first_position(array, length, target, &position)) {
        if (printf("%zu\n", position) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("-1\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}