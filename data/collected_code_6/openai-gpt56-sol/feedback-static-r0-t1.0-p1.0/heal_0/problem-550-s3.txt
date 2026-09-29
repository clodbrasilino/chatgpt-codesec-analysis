#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int find_maximum(const int array[], size_t length, int *maximum)
{
    size_t left;
    size_t right;

    if (array == NULL || maximum == NULL || length == 0U) {
        return -1;
    }

    left = 0U;
    right = length - 1U;

    while (left < right) {
        size_t middle = left + (right - left) / 2U;

        if (array[middle] > array[right]) {
            left = middle + 1U;
        } else if (array[middle] < array[right]) {
            right = middle;
        } else {
            --right;
        }
    }

    *maximum = (left == 0U) ? array[length - 1U] : array[left - 1U];
    return 0;
}

int main(void)
{
    const int array[] = {4, 5, 6, 7, 1, 2, 3};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int maximum;

    if (find_maximum(array, length, &maximum) != 0) {
        fputs("Unable to find the maximum element.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Maximum element: %d\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}