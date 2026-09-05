#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int* find_max_indices(const int* arr, size_t size, size_t* result_size) {
    if (arr == NULL || result_size == NULL) {
        return NULL;
    }

    if (size == 0) {
        *result_size = 0;
        return NULL;
    }

    int max_val = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == max_val) {
            count++;
        }
    }

    if (count == 0) {
        *result_size = 0;
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        *result_size = 0;
        return NULL;
    }

    int* indices = (int*)malloc(count * sizeof(int));
    if (indices == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == max_val) {
            indices[idx++] = (int)i;
        }
    }

    *result_size = count;
    return indices;
}

int main(void) {
    int arr[] = {4, 8, 3, 8, 1, 8, 2};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(arr)/sizeof(arr[0])', assigned value is 7
     */
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t result_size = 0;

    /* Possible weaknesses found:
     *  Condition 'size==0' is always false [knownConditionTrueFalse]
     *  Condition 'size==0' is always false
     */
    if (size == 0) {
        printf("Array is empty.\n");
        return 0;
    }

    int* indices = find_max_indices(arr, size, &result_size);

    if (indices != NULL && result_size > 0) {
        printf("Max value found at indices: ");
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", indices[i]);
        }
        printf("\n");
        free(indices);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}