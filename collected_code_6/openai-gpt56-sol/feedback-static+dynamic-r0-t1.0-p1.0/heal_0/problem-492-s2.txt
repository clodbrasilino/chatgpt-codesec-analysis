#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_search(const int *array, size_t length, int target, size_t *index)
{
    size_t left;
    size_t right;

    if (array == NULL || index == NULL || length == 0U) {
        return 0;
    }

    left = 0U;
    right = length;

    while (left < right) {
        size_t middle = left + (right - left) / 2U;

        if (array[middle] < target) {
            left = middle + 1U;
        } else {
            right = middle;
        }
    }

    if (left < length && array[left] == target) {
        *index = left;
        return 1;
    }

    return 0;
}

int main(void)
{
    static const int values[] = {1, 3, 5, 7, 9, 11, 13, 15};
    const size_t length = sizeof(values) / sizeof(values[0]);
    int target;
    size_t index;

    if (printf("Enter an integer to search for: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &target) != 1) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (binary_search(values, length, target, &index) != 0) {
        if (printf("Found at index %zu.\n", index) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("Not found.") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}