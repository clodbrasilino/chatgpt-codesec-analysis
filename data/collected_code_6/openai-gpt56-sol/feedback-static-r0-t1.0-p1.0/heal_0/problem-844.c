#include <stdio.h>
#include <stdlib.h>

static int find_kth_odd_then_even(const int *array, size_t length, size_t k, int *result)
{
    if (array == NULL || result == NULL || k == 0 || k > length) {
        return 0;
    }

    size_t position = 0;

    for (size_t i = 0; i < length; ++i) {
        if (array[i] % 2 != 0) {
            ++position;
            if (position == k) {
                *result = array[i];
                return 1;
            }
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] % 2 == 0) {
            ++position;
            if (position == k) {
                *result = array[i];
                return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    int array[] = {2, 7, 4, 9, 1, 6, 3, 8};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const size_t k = 5;
    int result = 0;

    if (!find_kth_odd_then_even(array, length, k, &result)) {
        fputs("Unable to find the requested element.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}