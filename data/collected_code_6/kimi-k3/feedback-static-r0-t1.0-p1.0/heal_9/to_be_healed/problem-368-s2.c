#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    int *data;
    size_t size;
} IntTuple;

IntTuple* tuple_create(const int *data, size_t size) {
    if (data == NULL || size == 0) {
        return NULL;
    }
    
    if (size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    
    size_t total_size = size * sizeof(int);
    
    IntTuple *tuple = malloc(sizeof(IntTuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->data = malloc(total_size);
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->data, data, total_size);
    tuple->size = size;
    
    return tuple;
}

IntTuple* tuple_repeat(const IntTuple *tuple, size_t n) {
    if (tuple == NULL || tuple->data == NULL || n == 0) {
        return NULL;
    }
    
    if (tuple->size > SIZE_MAX / n) {
        return NULL;
    }
    
    size_t new_size = tuple->size * n;
    
    if (new_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    
    size_t total_size = new_size * sizeof(int);
    size_t copy_size = tuple->size * sizeof(int);
    
    IntTuple *result = malloc(sizeof(IntTuple));
    if (result == NULL) {
        return NULL;
    }
    
    result->data = malloc(total_size);
    if (result->data == NULL) {
        free(result);
        return NULL;
    }
    
    for (size_t i = 0; i < n; i++) {
        size_t offset = i * copy_size;
        if (offset > total_size || copy_size > total_size - offset) {
            free(result->data);
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy((char *)result->data + offset, tuple->data, copy_size);
    }
    
    result->size = new_size;
    
    return result;
}

void tuple_destroy(IntTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        free(tuple);
    }
}

void tuple_print(const IntTuple *tuple) {
    if (tuple == NULL || tuple->data == NULL) {
        printf("()\n");
        return;
    }
    
    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d", tuple->data[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    int original_data[] = {1, 2, 3};
    size_t original_size = sizeof(original_data) / sizeof(original_data[0]);
    size_t repeat_count = 3;
    
    IntTuple *original = tuple_create(original_data, original_size);
    if (original == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }
    
    IntTuple *repeated = tuple_repeat(original, repeat_count);
    if (repeated == NULL) {
        fprintf(stderr, "Failed to repeat tuple\n");
        tuple_destroy(original);
        return EXIT_FAILURE;
    }
    
    printf("Original: ");
    tuple_print(original);
    
    printf("Repeated %zu times: ", repeat_count);
    tuple_print(repeated);
    
    tuple_destroy(original);
    tuple_destroy(repeated);
    
    return EXIT_SUCCESS;
}