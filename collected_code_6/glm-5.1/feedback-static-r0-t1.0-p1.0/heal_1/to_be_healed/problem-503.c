#include <stdio.h>
#include <stdlib.h>

int *add_consecutive(const int *list, size_t size, size_t *result_size) {
    if (list == NULL || result_size == NULL) {
        return NULL;
    }

    if (size < 2) {
        *result_size = 0;
        return NULL;
    }

    *result_size = size - 1;
    int *result = (int *)malloc(*result_size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *result_size; i++) {
        result[i] = list[i] + list[i + 1];
    }

    return result;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(list)/sizeof(list[0])', assigned value is 5
     */
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t result_size = 0;

    int *result = add_consecutive(list, size, &result_size);

    if (result != NULL) {
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        /* Possible weaknesses found:
         *  Condition 'size<2' is always false [knownConditionTrueFalse]
         *  Condition 'size<2' is always false
         */
        if (size < 2) {
            printf("List size is less than 2.\n");
        } else {
            printf("Memory allocation failed.\n");
        }
    }

    return 0;
}