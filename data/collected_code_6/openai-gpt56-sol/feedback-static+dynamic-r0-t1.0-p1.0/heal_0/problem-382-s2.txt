#include <stdio.h>
#include <stddef.h>

static size_t rotation_count(const int array[], size_t length)
{
    size_t left = 0;
    size_t right = length - 1;

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (array[middle] < array[right]) {
            right = middle;
        } else if (array[middle] > array[right]) {
            left = middle + 1;
        } else {
            --right;
        }
    }

    return left;
}

int main(void)
{
    int array[] = {15, 18, 2, 3, 6, 12};
    const size_t length = sizeof array / sizeof array[0];

    if (length == 0) {
        fputs("The array must not be empty.\n", stderr);
        return 1;
    }

    printf("Number of rotations: %zu\n", rotation_count(array, length));
    return 0;
}