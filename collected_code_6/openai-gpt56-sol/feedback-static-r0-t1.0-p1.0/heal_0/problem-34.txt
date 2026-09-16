#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

static bool find_missing_number(const int array[], size_t length, int *missing)
{
    if (array == NULL || missing == NULL || length == 0U) {
        return false;
    }

    if (array[0] != 1) {
        *missing = 1;
        return true;
    }

    size_t left = 0U;
    size_t right = length;

    while (left < right) {
        size_t middle = left + (right - left) / 2U;

        if (array[middle] == (int)(middle + 1U)) {
            left = middle + 1U;
        } else {
            right = middle;
        }
    }

    *missing = (int)(left + 1U);
    return true;
}

int main(void)
{
    const int array[] = {1, 2, 3, 4, 6, 7, 8};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int missing = 0;

    if (!find_missing_number(array, length, &missing)) {
        (void)fprintf(stderr, "Unable to find the missing number.\n");
        return 1;
    }

    if (printf("Missing number: %d\n", missing) < 0) {
        return 1;
    }

    return 0;
}