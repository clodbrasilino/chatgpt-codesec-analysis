#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple* create_tuple(size_t size) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (t == NULL) exit(EXIT_FAILURE);
    t->data = (int*)calloc(size, sizeof(int));
    if (t->data == NULL) { free(t); exit(EXIT_FAILURE); }
    t->size = size;
    return t;
}

int get_tuple_item(const Tuple* t, size_t index) {
    if (index >= t->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return t->data[index];
}

void destroy_tuple(Tuple* t) {
    free(t->data);
    free(t);
}

int main() {
    size_t size = 5;
    Tuple* my_tuple = create_tuple(size);

    for (size_t i = 0; i < size; ++i) {
        my_tuple->data[i] = i * 10;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d\n", get_tuple_item(my_tuple, i));
    }

    destroy_tuple(my_tuple);
    return 0;
}