#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int find_single_element(const int *array, size_t length, int *result)
{
    size_t low;
    size_t high;

    if (array == NULL || result == NULL || length == 0U || length % 2U == 0U) {
        return 0;
    }

    low = 0U;
    high = length - 1U;

    while (low < high) {
        size_t middle = low + (high - low) / 2U;

        if (middle % 2U != 0U) {
            --middle;
        }

        if (array[middle] == array[middle + 1U]) {
            low = middle + 2U;
        } else {
            high = middle;
        }
    }

    *result = array[low];
    return 1;
}

int main(void)
{
    const int array[] = {1, 1, 2, 2, 3, 4, 4, 5, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int result;

    if (!find_single_element(array, length, &result)) {
        (void)fprintf(stderr, "Unable to find the unique element.\n");
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}