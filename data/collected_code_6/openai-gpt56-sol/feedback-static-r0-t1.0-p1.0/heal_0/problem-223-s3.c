#include <stdio.h>
#include <stdlib.h>

static int has_majority_element(const int array[], size_t length, int *majority)
{
    if (array == NULL || majority == NULL || length == 0U) {
        return 0;
    }

    size_t candidate_index = length / 2U;
    int candidate = array[candidate_index];
    size_t first = 0U;
    size_t last = candidate_index;

    while (first < last) {
        size_t middle = first + (last - first) / 2U;

        if (array[middle] < candidate) {
            first = middle + 1U;
        } else {
            last = middle;
        }
    }

    if (length / 2U < length - first &&
        array[first + length / 2U] == candidate) {
        *majority = candidate;
        return 1;
    }

    return 0;
}

int main(void)
{
    int array[] = {1, 2, 2, 2, 2, 3, 4};
    size_t length = sizeof(array) / sizeof(array[0]);
    int majority = 0;

    if (has_majority_element(array, length, &majority) != 0) {
        if (printf("Majority element: %d\n", majority) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No majority element\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}