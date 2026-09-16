#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_monotonic(const int *array, size_t length)
{
    bool nondecreasing = true;
    bool nonincreasing = true;

    if (array == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 1U; i < length; ++i) {
        if (array[i] < array[i - 1U]) {
            nondecreasing = false;
        }

        if (array[i] > array[i - 1U]) {
            nonincreasing = false;
        }
    }

    return nondecreasing || nonincreasing;
}

int main(void)
{
    const int array[] = {1, 2, 2, 3, 4};
    const size_t length = sizeof(array) / sizeof(array[0]);

    if (is_monotonic(array, length)) {
        if (printf("The array is monotonic.\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("The array is not monotonic.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}