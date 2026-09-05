#include <stdio.h>
#include <stdlib.h>

int *access_elements(const int *list, size_t list_size, const size_t *indices, size_t indices_size, size_t *result_size) {
    if (list == NULL || indices == NULL || result_size == NULL) {
        return NULL;
    }

    if (indices_size == 0) {
        *result_size = 0;
        return NULL;
    }

    int *result = (int *)malloc(indices_size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < indices_size; i++) {
        if (indices[i] < list_size) {
            result[valid_count] = list[indices[i]];
            valid_count++;
        }
    }

    if (valid_count == 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    if (valid_count < indices_size) {
        int *shrunk_result = (int *)realloc(result, valid_count * sizeof(int));
        if (shrunk_result != NULL) {
            result = shrunk_result;
        }
    }

    *result_size = valid_count;
    return result;
}

int main(void) {
    int list[] = {10, 20, 30, 40, 50};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    size_t indices[] = {0, 2, 4, 5, 1};
    /* Possible weaknesses found:
     *  Assignment 'indices_size=sizeof(indices)/sizeof(indices[0])', assigned value is 5
     */
    size_t indices_size = sizeof(indices) / sizeof(indices[0]);

    size_t result_size = 0;
    int *result = access_elements(list, list_size, indices, indices_size, &result_size);

    if (result != NULL) {
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        /* Possible weaknesses found:
         *  Condition 'indices_size>0' is always true [knownConditionTrueFalse]
         *  Condition 'indices_size>0' is always true
         */
        if (result_size == 0 && indices_size > 0) {
            printf("No valid indices found.\n");
        } else {
            printf("Allocation failed or empty request.\n");
        }
    }

    return 0;
}