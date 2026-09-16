#include <stdio.h>
#include <stdlib.h>

static int sequential_search(const int array[], size_t length, int target, size_t *index)
{
    if (array == NULL || index == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == target) {
            *index = i;
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    int array[] = {12, 7, 19, 3, 25, 8};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int target = 0;
    size_t index = 0;

    if (printf("Enter the element to search for: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (sequential_search(array, length, target, &index) != 0) {
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