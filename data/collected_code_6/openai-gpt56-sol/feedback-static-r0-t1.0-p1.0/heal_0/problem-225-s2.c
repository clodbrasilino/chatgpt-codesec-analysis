#include <stdio.h>
#include <stdlib.h>

static int find_minimum(const int array[], size_t length, int *minimum)
{
    if (array == NULL || minimum == NULL || length == 0U) {
        return -1;
    }

    size_t left = 0U;
    size_t right = length - 1U;

    while (left < right) {
        const size_t middle = left + (right - left) / 2U;

        if (array[middle] < array[right]) {
            right = middle;
        } else if (array[middle] > array[right]) {
            left = middle + 1U;
        } else {
            --right;
        }
    }

    *minimum = array[left];
    return 0;
}

int main(void)
{
    const int array[] = {4, 5, 6, 7, 0, 1, 2};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int minimum = 0;

    if (find_minimum(array, length, &minimum) != 0) {
        fputs("Failed to find the minimum element.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Minimum element: %d\n", minimum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}