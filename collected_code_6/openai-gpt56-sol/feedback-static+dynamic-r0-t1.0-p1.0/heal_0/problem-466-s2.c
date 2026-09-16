#include <stdio.h>
#include <stdlib.h>

static int find_peak(const int *array, size_t length, size_t *peak_index)
{
    size_t left;
    size_t right;

    if (array == NULL || peak_index == NULL || length == 0U) {
        return 0;
    }

    left = 0U;
    right = length - 1U;

    while (left < right) {
        size_t middle = left + (right - left) / 2U;

        if (array[middle] < array[middle + 1U]) {
            left = middle + 1U;
        } else {
            right = middle;
        }
    }

    *peak_index = left;
    return 1;
}

int main(void)
{
    int array[] = {1, 3, 20, 4, 1, 0};
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t peak_index;

    if (!find_peak(array, length, &peak_index)) {
        fputs("Failed to find a peak element.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Peak element: %d at index %zu\n",
               array[peak_index], peak_index) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}