#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int count_before_record(const Tuple *tuple, int record) {
    if (tuple == NULL) {
        return -1;
    }
    
    size_t i;
    for (i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] == record) {
            return (int)i;
        }
    }
    
    return -1;
}

Tuple *create_tuple(const int *data, size_t size) {
    if (data == NULL && size > 0) {
        return NULL;
    }
    
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->elements = (int *)malloc(sizeof(int) * size);
    if (tuple->elements == NULL && size > 0) {
        free(tuple);
        return NULL;
    }
    
    if (size > 0) {
        memcpy(tuple->elements, data, sizeof(int) * size);
    }
    
    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    free(tuple->elements);
    free(tuple);
}

int main(void) {
    int arr[] = {5, 10, 15, 20, 25, 30};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    Tuple *t = create_tuple(arr, n);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }
    
    int target = 20;
    int count = count_before_record(t, target);
    
    if (count >= 0) {
        printf("Element count before record %d: %d\n", target, count);
    } else {
        printf("Record %d not found in tuple\n", target);
    }
    
    free_tuple(t);
    return EXIT_SUCCESS;
}