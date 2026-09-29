#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

int minimum_jumps(const size_t array[], size_t length, size_t *result)
{
    size_t jumps = 0;
    size_t current_end = 0;
    size_t farthest = 0;

    if (array == NULL || result == NULL || length == 0) {
        return -1;
    }

    if (length == 1) {
        *result = 0;
        return 0;
    }

    for (size_t i = 0; i < length - 1; ++i) {
        size_t reachable;

        if (array[i] > (length - 1) - i) {
            reachable = length - 1;
        } else {
            reachable = i + array[i];
        }

        if (reachable > farthest) {
            farthest = reachable;
        }

        if (i == current_end) {
            if (farthest <= i || jumps == SIZE_MAX) {
                return -1;
            }

            ++jumps;
            current_end = farthest;

            if (current_end >= length - 1) {
                *result = jumps;
                return 0;
            }
        }
    }

    return -1;
}

int main(void)
{
    const size_t array[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t result;

    if (minimum_jumps(array, length, &result) != 0) {
        if (fputs("The end cannot be reached.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Minimum number of jumps: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}