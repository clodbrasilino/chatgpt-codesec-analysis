#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

static bool find_maximum(const int array[], size_t length, int *maximum)
{
    if (array == NULL || maximum == NULL || length == 0U) {
        return false;
    }

    size_t left = 0U;
    size_t right = length - 1U;

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

    size_t minimum_index = left;
    size_t maximum_index = minimum_index == 0U ? length - 1U : minimum_index - 1U;

    *maximum = array[maximum_index];
    return true;
}

int main(void)
{
    const int array[] = {13, 18, 25, 2, 8, 10};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int maximum = 0;

    if (!find_maximum(array, length, &maximum)) {
        fputs("Unable to find the maximum element.\n", stderr);
        return 1;
    }

    printf("Maximum element: %d\n", maximum);
    return 0;
}