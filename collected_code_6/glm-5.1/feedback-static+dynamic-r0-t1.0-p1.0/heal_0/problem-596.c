#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *items;
    size_t count;
    size_t item_size;
} Tuple;

Tuple* tuple_create(size_t count, size_t item_size) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->items = malloc(count * item_size);
    if (t->items == NULL) {
        free(t);
        return NULL;
    }
    t->count = count;
    t->item_size = item_size;
    return t;
}

size_t tuple_size(const Tuple *t) {
    if (t == NULL) {
        return 0;
    }
    return t->count;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->items);
        free(t);
    }
}

int main(void) {
    Tuple *t = tuple_create(5, sizeof(int));
    if (t == NULL) {
        return EXIT_FAILURE;
    }
    size_t size = tuple_size(t);
    printf("%zu\n", size);
    tuple_free(t);
    return EXIT_SUCCESS;
}