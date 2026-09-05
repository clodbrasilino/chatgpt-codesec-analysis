#include <stdio.h>
#include <stdlib.h>

void add_consecutive(const int *list, size_t size, int *result, size_t *result_size)
{
    size_t i;

    if (size == 0) {
        *result_size = 0;
        return;
    }

    *result_size = size - 1;

    for (i = 0; i < *result_size; i++) {
        result[i] = list[i] + list[i + 1];
    }
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(list)/sizeof(list[0])', assigned value is 5
     */
    size_t size = sizeof(list) / sizeof(list[0]);
    int *result = NULL;
    size_t result_size = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    /* Possible weaknesses found:
     *  Condition 'size>1' is always true
     *  Condition 'size>1' is always true [knownConditionTrueFalse]
     */
    if (size > 1) {
        result = (int *)malloc((size - 1) * sizeof(int));
        if (result == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        add_consecutive(list, size, result, &result_size);

        printf("Original list: ");
        for (i = 0; i < size; i++) {
            printf("%d ", list[i]);
        }
        printf("\n");

        printf("Consecutive sums: ");
        for (i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");

        free(result);
        result = NULL;
    } else {
        printf("List must contain at least 2 elements\n");
    }

    return EXIT_SUCCESS;
}