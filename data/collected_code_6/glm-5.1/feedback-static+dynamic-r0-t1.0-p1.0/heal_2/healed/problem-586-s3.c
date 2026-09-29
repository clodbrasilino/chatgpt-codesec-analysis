#include <stdio.h>
#include <stdlib.h>

int* split_and_add(const int* arr, size_t size, size_t split, size_t* result_size) {
    if (size == 0) {
        *result_size = 0;
        return NULL;
    }

    size_t split_pos = split % size;
    int* result = malloc(size * sizeof(int));
    if (!result) {
        *result_size = 0;
        return NULL;
    }

    if (split_pos == 0) {
        for (size_t i = 0; i < size; i++) {
            result[i] = arr[i];
        }
    } else {
        for (size_t i = 0; i < size - split_pos; i++) {
            result[i] = arr[split_pos + i];
        }
        for (size_t i = 0; i < split_pos; i++) {
            result[size - split_pos + i] = arr[i];
        }
    }

    *result_size = size;
    return result;
}

int main(void) {
    const int arr[] = {1, 2, 3, 4, 5, 6, 7};
    const size_t size = 7;
    size_t split = 2;
    size_t result_size;

    int* result = split_and_add(arr, size, split, &result_size);

    if (result != NULL) {
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        if (size == 0) {
            fprintf(stderr, "Input array is empty\n");
        } else {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }

    return 0;
}