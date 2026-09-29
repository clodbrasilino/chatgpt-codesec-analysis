#include <stdio.h>
#include <stddef.h>

static int find_last_occurrence(const int array[], size_t length, int target, size_t *index)
{
    size_t left = 0;
    size_t right = length;

    if (array == NULL || index == NULL || length == 0) {
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

    if (left > 0 && array[left - 1] == target) {
        *index = left - 1;
        return 1;
    }

    return 0;
}

int main(void)
{
    const int array[] = {1, 2, 2, 2, 3, 4, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const int target = 2;
    size_t index = 0;

    if (find_last_occurrence(array, length, target, &index)) {
        if (printf("%zu\n", index) < 0) {
            return 1;
        }
    } else {
        if (printf("-1\n") < 0) {
            return 1;
        }
    }

    return 0;
}