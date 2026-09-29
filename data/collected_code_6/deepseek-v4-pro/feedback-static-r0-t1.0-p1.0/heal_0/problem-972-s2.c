#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    void **elements;
    size_t size;
} Tuple;

Tuple *create_tuple(void **elements, size_t size) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->elements = (void **)malloc(size * sizeof(void *));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        tuple->elements[i] = elements[i];
    }
    
    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

Tuple *concatenate_tuples(Tuple *tuple1, Tuple *tuple2) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return NULL;
    }
    
    void **elements = (void **)malloc(2 * sizeof(void *));
    if (elements == NULL) {
        return NULL;
    }
    
    elements[0] = (void *)tuple1;
    elements[1] = (void *)tuple2;
    
    Tuple *result = create_tuple(elements, 2);
    free(elements);
    
    return result;
}

void print_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        printf("NULL\n");
        return;
    }
    
    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] == NULL) {
            printf("NULL");
        } else if (((Tuple *)tuple->elements[i])->size > 0 && 
                   ((Tuple *)tuple->elements[i])->elements != NULL) {
            print_tuple((Tuple *)tuple->elements[i]);
        } else {
            printf("%p", tuple->elements[i]);
        }
        
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")");
}

int main() {
    int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;
    
    void *elements1[] = {(void *)&a, (void *)&b};
    void *elements2[] = {(void *)&c, (void *)&d};
    
    Tuple *tuple1 = create_tuple(elements1, 2);
    Tuple *tuple2 = create_tuple(elements2, 2);
    
    if (tuple1 == NULL || tuple2 == NULL) {
        free_tuple(tuple1);
        free_tuple(tuple2);
        return 1;
    }
    
    Tuple *result = concatenate_tuples(tuple1, tuple2);
    if (result == NULL) {
        free_tuple(tuple1);
        free_tuple(tuple2);
        return 1;
    }
    
    print_tuple(result);
    printf("\n");
    
    free_tuple(result);
    free_tuple(tuple1);
    free_tuple(tuple2);
    
    return 0;
}