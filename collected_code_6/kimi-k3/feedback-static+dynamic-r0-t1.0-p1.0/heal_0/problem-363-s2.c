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
    
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->data = malloc(size * sizeof(int));
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
    if (tuple == NULL || tuple->data == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        tuple->data[i] += k;
    }
    
    return 0;
}

void print_tuple(const Tuple *tuple) {
    if (tuple == NULL || tuple->data == NULL) {
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
    Tuple *tuple = create_tuple(5);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }
    
    tuple->data[0] = 1;
    tuple->data[1] = 2;
    tuple->data[2] = 3;
    tuple->data[3] = 4;
    tuple->data[4] = 5;
    
    printf("Original tuple: ");
    print_tuple(tuple);
    
    int k = 10;
    if (add_k_elements(tuple, k) != 0) {
        fprintf(stderr, "Failed to add elements\n");
        destroy_tuple(tuple);
        return EXIT_FAILURE;
    }
    
    printf("After adding %d: ", k);
    print_tuple(tuple);
    
    destroy_tuple(tuple);
    return EXIT_SUCCESS;
}