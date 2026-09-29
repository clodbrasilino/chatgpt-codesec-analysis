#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple* create_tuple(size_t size) {
    if (size == 0) {
        return NULL;
    }
    
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->data = (int*)calloc(size, sizeof(int));
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = size;
    return tuple;
}

void destroy_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        free(tuple);
    }
}

int add_k_elements(Tuple *tuple, int k) {
    if (tuple == NULL || tuple->data == NULL || tuple->size == 0) {
        return -1;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        tuple->data[i] += k;
    }
    
    return 0;
}

int set_tuple_element(Tuple *tuple, size_t index, int value) {
    if (tuple == NULL || tuple->data == NULL || index >= tuple->size) {
        return -1;
    }
    
    tuple->data[index] = value;
    return 0;
}

void print_tuple(const Tuple *tuple) {
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
    size_t size = 5;
    int k = 10;
    
    Tuple *tuple = create_tuple(size);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (set_tuple_element(tuple, i, (int)(i + 1)) != 0) {
            fprintf(stderr, "Failed to set element\n");
            destroy_tuple(tuple);
            return EXIT_FAILURE;
        }
    }
    
    printf("Original tuple: ");
    print_tuple(tuple);
    
    if (add_k_elements(tuple, k) != 0) {
        fprintf(stderr, "Failed to add k elements\n");
        destroy_tuple(tuple);
        return EXIT_FAILURE;
    }
    
    printf("Tuple after adding %d: ", k);
    print_tuple(tuple);
    
    destroy_tuple(tuple);
    return EXIT_SUCCESS;
}