#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple *list_to_tuple(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        Tuple *empty = malloc(sizeof(Tuple));
        if (empty == NULL) {
            return NULL;
        }
        empty->elements = NULL;
        empty->size = 0;
        return empty;
    }
    
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    
    t->elements = malloc(size * sizeof(int));
    if (t->elements == NULL) {
        free(t);
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        t->elements[i] = list[i];
    }
    t->size = size;
    
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->elements);
        free(t);
    }
}

int main(void) {
    int list[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(list) / sizeof(list[0]);
    
    Tuple *t = list_to_tuple(list, size);
    if (t == NULL) {
        return EXIT_FAILURE;
    }
    
    printf("(");
    for (size_t i = 0; i < t->size; i++) {
        printf("%d", t->elements[i]);
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
    
    free_tuple(t);
    
    return EXIT_SUCCESS;
}