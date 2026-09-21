#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple repeat_tuple(const Tuple *tuple, size_t n) {
    Tuple result;

    if (tuple == NULL || tuple->elements == NULL || n == 0 || tuple->size == 0) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }

    if (tuple->size > SIZE_MAX / n) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }

    size_t total_elements = tuple->size * n;

    if (total_elements > SIZE_MAX / sizeof(int)) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }

    result.size = total_elements;
    result.elements = (int *)malloc(result.size * sizeof(int));

    if (result.elements == NULL) {
        result.size = 0;
        return result;
    }

    size_t element_size = sizeof(int);
    size_t copy_size = tuple->size * element_size;

    for (size_t i = 0; i < n; i++) {
        size_t offset = i * tuple->size;

        if (offset + tuple->size > result.size) {
            free(result.elements);
            result.elements = NULL;
            result.size = 0;
            return result;
        }

        memcpy(result.elements + offset, tuple->elements, copy_size);
    }

    return result;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    int arr[] = {1, 2, 3};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    int *heap_arr = (int *)malloc(arr_size * sizeof(int));

    if (heap_arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    memcpy(heap_arr, arr, arr_size * sizeof(int));

    Tuple original;
    original.elements = heap_arr;
    original.size = arr_size;

    size_t n = 4;
    Tuple repeated = repeat_tuple(&original, n);

    if (repeated.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_tuple(&original);
        return 1;
    }

    printf("Repeated tuple: ");
    for (size_t i = 0; i < repeated.size; i++) {
        printf("%d ", repeated.elements[i]);
    }
    printf("\n");

    free_tuple(&repeated);
    free_tuple(&original);

    return 0;
}