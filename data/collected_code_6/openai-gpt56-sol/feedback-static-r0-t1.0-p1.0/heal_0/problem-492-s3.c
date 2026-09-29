#include <stdio.h>
#include <stdlib.h>

static int binary_search(const int array[], size_t length, int target, size_t *index)
{
    size_t left = 0;
    size_t right = length;

    if (array == NULL || index == NULL) {
        return -1;
    }

    while (left < right) {
        size_t middle = left + (right - left) / 2U;

        if (array[middle] == target) {
            *index = middle;
            return 1;
        }

        if (array[middle] < target) {
            left = middle + 1U;
        } else {
            right = middle;
        }
    }

    return 0;
}

int main(void)
{
    int array[] = {1, 3, 5, 7, 9, 11, 13, 15};
    const size_t length = sizeof array / sizeof array[0];
    int target;
    size_t index = 0;
    int result;

    if (printf("Enter the element to search for: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = binary_search(array, length, target, &index);

    if (result < 0) {
        fprintf(stderr, "Binary search failed.\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        if (printf("Element found at index %zu.\n", index) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Element not found.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}