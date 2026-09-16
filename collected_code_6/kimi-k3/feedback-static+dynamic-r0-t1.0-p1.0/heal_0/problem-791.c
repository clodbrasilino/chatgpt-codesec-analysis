#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
    int is_nested;
    void *nested;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
    size_t capacity;
} Tuple;

Tuple* tuple_create(size_t initial_capacity) {
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->elements = malloc(initial_capacity * sizeof(TupleElement));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->count = 0;
    tuple->capacity = initial_capacity;
    return tuple;
}

void tuple_destroy(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].is_nested && tuple->elements[i].nested != NULL) {
            tuple_destroy((Tuple*)tuple->elements[i].nested);
        }
    }
    
    free(tuple->elements);
    free(tuple);
}

int tuple_add_int(Tuple *tuple, int value) {
    if (tuple == NULL) {
        return -1;
    }
    
    if (tuple->count >= tuple->capacity) {
        size_t new_capacity = tuple->capacity * 2;
        TupleElement *new_elements = realloc(tuple->elements, 
                                             new_capacity * sizeof(TupleElement));
        if (new_elements == NULL) {
            return -1;
        }
        tuple->elements = new_elements;
        tuple->capacity = new_capacity;
    }
    
    tuple->elements[tuple->count].data = malloc(sizeof(int));
    if (tuple->elements[tuple->count].data == NULL) {
        return -1;
    }
    
    *tuple->elements[tuple->count].data = value;
    tuple->elements[tuple->count].size = sizeof(int);
    tuple->elements[tuple->count].capacity = sizeof(int);
    tuple->elements[tuple->count].is_nested = 0;
    tuple->elements[tuple->count].nested = NULL;
    tuple->count++;
    
    return 0;
}

int tuple_add_nested(Tuple *tuple, Tuple *nested) {
    if (tuple == NULL || nested == NULL) {
        return -1;
    }
    
    if (tuple->count >= tuple->capacity) {
        size_t new_capacity = tuple->capacity * 2;
        TupleElement *new_elements = realloc(tuple->elements, 
                                             new_capacity * sizeof(TupleElement));
        if (new_elements == NULL) {
            return -1;
        }
        tuple->elements = new_elements;
        tuple->capacity = new_capacity;
    }
    
    tuple->elements[tuple->count].data = NULL;
    tuple->elements[tuple->count].size = 0;
    tuple->elements[tuple->count].capacity = 0;
    tuple->elements[tuple->count].is_nested = 1;
    tuple->elements[tuple->count].nested = nested;
    tuple->count++;
    
    return 0;
}

int tuple_remove_nested(Tuple *tuple) {
    if (tuple == NULL) {
        return -1;
    }
    
    size_t write_index = 0;
    
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].is_nested) {
            if (tuple->elements[i].nested != NULL) {
                tuple_destroy((Tuple*)tuple->elements[i].nested);
            }
        } else {
            if (write_index != i) {
                tuple->elements[write_index] = tuple->elements[i];
            }
            write_index++;
        }
    }
    
    tuple->count = write_index;
    return 0;
}

void tuple_print(Tuple *tuple) {
    if (tuple == NULL) {
        printf("NULL\n");
        return;
    }
    
    printf("(");
    for (size_t i = 0; i < tuple->count; i++) {
        if (tuple->elements[i].is_nested) {
            tuple_print((Tuple*)tuple->elements[i].nested);
        } else {
            printf("%d", *tuple->elements[i].data);
        }
        
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf(")");
}

int main(void) {
    Tuple *tuple = tuple_create(4);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }
    
    Tuple *nested1 = tuple_create(2);
    if (nested1 == NULL) {
        fprintf(stderr, "Failed to create nested tuple\n");
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    Tuple *nested2 = tuple_create(2);
    if (nested2 == NULL) {
        fprintf(stderr, "Failed to create nested tuple\n");
        tuple_destroy(nested1);
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_int(tuple, 1) != 0) {
        fprintf(stderr, "Failed to add element\n");
        tuple_destroy(nested2);
        tuple_destroy(nested1);
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_int(nested1, 2) != 0 || tuple_add_int(nested1, 3) != 0) {
        fprintf(stderr, "Failed to add element\n");
        tuple_destroy(nested2);
        tuple_destroy(nested1);
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_nested(tuple, nested1) != 0) {
        fprintf(stderr, "Failed to add nested tuple\n");
        tuple_destroy(nested2);
        tuple_destroy(nested1);
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_int(tuple, 4) != 0) {
        fprintf(stderr, "Failed to add element\n");
        tuple_destroy(nested2);
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_int(nested2, 5) != 0) {
        fprintf(stderr, "Failed to add element\n");
        tuple_destroy(nested2);
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_nested(tuple, nested2) != 0) {
        fprintf(stderr, "Failed to add nested tuple\n");
        tuple_destroy(nested2);
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (tuple_add_int(tuple, 6) != 0) {
        fprintf(stderr, "Failed to add element\n");
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    printf("Original tuple: ");
    tuple_print(tuple);
    printf("\n");
    
    if (tuple_remove_nested(tuple) != 0) {
        fprintf(stderr, "Failed to remove nested tuples\n");
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    printf("After removing nested tuples: ");
    tuple_print(tuple);
    printf("\n");
    
    tuple_destroy(tuple);
    
    return EXIT_SUCCESS;
}