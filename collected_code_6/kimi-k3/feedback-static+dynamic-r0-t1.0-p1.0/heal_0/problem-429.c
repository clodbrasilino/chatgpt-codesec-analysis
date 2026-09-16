#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple *create_tuple(size_t size) {
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->data = malloc(size * sizeof(int));
    if (t->data == NULL) {
        free(t);
        return NULL;
    }
    t->size = size;
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        free(t);
    }
}

Tuple *elementwise_and(const Tuple *t1, const Tuple *t2) {
    if (t1 == NULL || t2 == NULL || t1->size != t2->size || t1->size == 0) {
        return NULL;
    }
    
    Tuple *result = create_tuple(t1->size);
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < t1->size; i++) {
        result->data[i] = t1->data[i] & t2->data[i];
    }
    
    return result;
}

void print_tuple(const Tuple *t) {
    if (t == NULL || t->size == 0) {
        printf("()\n");
        return;
    }
    
    printf("(");
    for (size_t i = 0; i < t->size; i++) {
        printf("%d", t->data[i]);
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    Tuple *t1 = create_tuple(4);
    if (t1 == NULL) {
        return EXIT_FAILURE;
    }
    t1->data[0] = 10;
    t1->data[1] = 4;
    t1->data[2] = 5;
    t1->data[3] = 6;
    
    Tuple *t2 = create_tuple(4);
    if (t2 == NULL) {
        free_tuple(t1);
        return EXIT_FAILURE;
    }
    t2->data[0] = 5;
    t2->data[1] = 6;
    t2->data[2] = 3;
    t2->data[3] = 2;
    
    printf("Tuple 1: ");
    print_tuple(t1);
    
    printf("Tuple 2: ");
    print_tuple(t2);
    
    Tuple *result = elementwise_and(t1, t2);
    if (result == NULL) {
        free_tuple(t1);
        free_tuple(t2);
        return EXIT_FAILURE;
    }
    
    printf("Elementwise AND: ");
    print_tuple(result);
    
    free_tuple(t1);
    free_tuple(t2);
    free_tuple(result);
    
    return EXIT_SUCCESS;
}