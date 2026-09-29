#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

int minimum_jumps(const int *array, size_t length, size_t *result)
{
    if (array == NULL || result == NULL || length == 0U) {
        return -1;
    }

    if (length == 1U) {
        *result = 0U;
        return 0;
    }

    if (array[0] <= 0) {
        return 1;
    }

    size_t farthest = (size_t)array[0];
    size_t current_end = farthest;
    size_t jumps = 1U;

    if (farthest >= length - 1U) {
        *result = jumps;
        return 0;
    }

    for (size_t i = 1U; i < length - 1U; ++i) {
        if (i > farthest) {
            return 1;
        }

        if (array[i] < 0) {
            return -1;
        }

        size_t reach;
        if ((size_t)array[i] > SIZE_MAX - i) {
            reach = SIZE_MAX;
        } else {
            reach = i + (size_t)array[i];
        }

        if (reach > farthest) {
            farthest = reach;
        }

        if (i == current_end) {
            if (farthest <= i) {
                return 1;
            }

            if (jumps == SIZE_MAX) {
                return -1;
            }

            ++jumps;
            current_end = farthest;

            if (current_end >= length - 1U) {
                *result = jumps;
                return 0;
            }
        }
    }

    return 1;
}

int main(void)
{
    int array[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t jumps = 0U;
    int status = minimum_jumps(array, length, &jumps);

    if (status == 0) {
        if (printf("%zu\n", jumps) < 0) {
            return EXIT_FAILURE;
        }
    } else if (status == 1) {
        if (fprintf(stderr, "The end is unreachable.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    } else {
        if (fprintf(stderr, "Invalid input or arithmetic error.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}