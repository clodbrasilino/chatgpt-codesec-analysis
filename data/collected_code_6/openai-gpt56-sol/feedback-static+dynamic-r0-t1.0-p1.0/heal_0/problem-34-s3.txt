#include <stdio.h>
#include <stdlib.h>

static int find_missing_number(const int *array, size_t length, int *missing)
{
    size_t left;
    size_t right;

    if (array == NULL || missing == NULL || length == 0U) {
        return -1;
    }

    left = 0U;
    right = length;

    while (left < right) {
        size_t middle = left + (right - left) / 2U;

        if (array[middle] == (int)middle + 1) {
            left = middle + 1U;
        } else {
            right = middle;
        }
    }

    *missing = (int)left + 1;
    return 0;
}

int main(void)
{
    const int array[] = {1, 2, 3, 4, 6, 7, 8};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int missing;

    if (find_missing_number(array, length, &missing) != 0) {
        fputs("Unable to find the missing number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Missing number: %d\n", missing) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}