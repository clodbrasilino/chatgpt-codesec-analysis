#include <stdio.h>
#include <stddef.h>

static int find_first_position(const int array[], size_t length, int target, size_t *position)
{
    size_t left = 0;
    size_t right = length;

    if (position == NULL || (array == NULL && length != 0)) {
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
        *position = left;
        return 1;
    }

    return 0;
}

int main(void)
{
    const int array[] = {1, 2, 2, 2, 3, 4, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const int target = 2;
    size_t position = 0;
    int result = find_first_position(array, length, target, &position);

    if (result < 0) {
        fputs("Invalid argument\n", stderr);
        return 1;
    }

    if (result == 1) {
        printf("First position: %zu\n", position);
    } else {
        puts("Element not found");
    }

    return 0;
}