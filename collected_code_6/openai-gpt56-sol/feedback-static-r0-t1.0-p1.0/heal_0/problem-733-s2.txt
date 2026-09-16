#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static ptrdiff_t find_first_occurrence(const int *array, size_t length, int target)
{
    size_t left = 0;
    size_t right = length;

    if (array == NULL && length != 0) {
        return -1;
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
        return (ptrdiff_t)left;
    }

    return -1;
}

int main(void)
{
    int array[] = {1, 2, 2, 2, 3, 4, 5};
    size_t length = sizeof(array) / sizeof(array[0]);
    int target = 2;
    ptrdiff_t index = find_first_occurrence(array, length, target);

    if (index >= 0) {
        if (printf("%td\n", index) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Not found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}