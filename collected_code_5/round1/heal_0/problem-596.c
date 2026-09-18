#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* elements;
    size_t size;
} Tuple;

void create_tuple(Tuple* t, size_t size) {
    if (t != NULL) {
        t->elements = (int*) malloc(sizeof(int) * size);
        if (t->elements != NULL) {
            t->size = size;
        }
        else {
            t->size = 0;
        }
    }
}

void delete_tuple(Tuple* t) {
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

size_t size_of_tuple(Tuple* t) {
    if (t != NULL) {
        return t->size;
    }
    else {
        return 0;
    }
}

int main() {
    Tuple t;
    create_tuple(&t, 5);
    printf("Size of the tuple is: %zu\n", size_of_tuple(&t));
    delete_tuple(&t);
    return 0;
}