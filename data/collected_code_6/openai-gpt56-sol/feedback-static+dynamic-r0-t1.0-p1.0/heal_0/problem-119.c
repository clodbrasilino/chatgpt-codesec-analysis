#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int find_single(const int *array, size_t length, int *result)
{
    if (array == NULL || result == NULL || length == 0U || length % 2U == 0U) {
        return 0;
    }

    size_t left = 0U;
    size_t right = length - 1U;

    while (left < right) {
        size_t middle = left + (right - left) / 2U;

        if (middle % 2U != 0U) {
            --middle;
        }

        if (array[middle] == array[middle + 1U]) {
            left = middle + 2U;
        } else {
            right = middle;
        }
    }

    *result = array[left];
    return 1;
}

int main(void)
{
    const int array[] = {1, 1, 2, 2, 3, 4, 4, 5, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int result = 0;

    if (!find_single(array, length, &result)) {
        (void)fprintf(stderr, "Unable to find the unique element.\n");
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}