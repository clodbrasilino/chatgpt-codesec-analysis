#include <stdio.h>
#include <stdlib.h>

static int has_majority_element(const int *array, size_t length, int *majority)
{
    size_t candidate_index;
    size_t count = 0U;
    size_t i;

    if (array == NULL || majority == NULL || length == 0U) {
        return 0;
    }

    candidate_index = length / 2U;

    for (i = 0U; i < length; ++i) {
        if (array[i] == array[candidate_index]) {
            ++count;
        }
    }

    if (count > length / 2U) {
        *majority = array[candidate_index];
        return 1;
    }

    return 0;
}

int main(void)
{
    int array[] = {1, 2, 2, 2, 2, 3, 4};
    const size_t length = sizeof(array) / sizeof(array[0]);
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