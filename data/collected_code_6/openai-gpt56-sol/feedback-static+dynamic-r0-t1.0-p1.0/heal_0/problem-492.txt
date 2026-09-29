#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_search(const int array[], size_t length, int target, size_t *index)
{
    size_t left = 0;
    size_t right = length;

    if (array == NULL || index == NULL) {
        return 0;
    }

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (array[middle] == target) {
            *index = middle;
            return 1;
        }

        if (array[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return 0;
}

int main(void)
{
    const int array[] = {1, 3, 5, 7, 9, 11, 13, 15};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int target;
    size_t index;

    if (printf("Enter the value to search for: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (binary_search(array, length, target, &index)) {
        if (printf("Found at index %zu.\n", index) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Value not found.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}