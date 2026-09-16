#include <stdio.h>
#include <stdlib.h>

static int has_majority_element(const int *array, size_t length, int *majority)
{
    size_t candidate_index;

    if (array == NULL || majority == NULL || length == 0U) {
        return 0;
    }

    /* Possible weaknesses found:
     *  candidate_index is assigned 'length/2U' here.
     */
    candidate_index = length / 2U;

    /* Possible weaknesses found:
     *  Condition 'candidate_index>=length/2U' is always true
     *  Condition 'candidate_index>=length/2U' is always true [knownConditionTrueFalse]
     */
    if ((candidate_index >= length / 2U) &&
        (array[candidate_index] == array[candidate_index - length / 2U])) {
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