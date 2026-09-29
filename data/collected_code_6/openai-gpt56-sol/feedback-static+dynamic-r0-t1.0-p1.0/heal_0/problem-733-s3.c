#include <stdio.h>
#include <stdlib.h>

static int find_first_occurrence(const int *array, size_t length, int target, size_t *index)
{
    if (array == NULL || index == NULL || length == 0U) {
        return 0;
    }

    size_t left = 0U;
    size_t right = length;

    while (left < right) {
        size_t middle = left + (right - left) / 2U;

        if (array[middle] < target) {
            left = middle + 1U;
        } else {
            right = middle;
        }
    }

    if (left < length && array[left] == target) {
        *index = left;
        return 1;
    }

    return 0;
}

int main(void)
{
    int array[] = {1, 2, 2, 2, 3, 4, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const int target = 2;
    size_t index = 0U;

    if (find_first_occurrence(array, length, target, &index)) {
        if (printf("%zu\n", index) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("-1\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}