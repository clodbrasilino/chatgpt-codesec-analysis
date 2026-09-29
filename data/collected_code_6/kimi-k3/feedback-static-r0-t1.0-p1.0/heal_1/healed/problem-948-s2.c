#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **items;
    size_t size;
} Tuple;

Tuple *tuple_create(size_t size) {
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->items = calloc(size, sizeof(void *));
    if (t->items == NULL) {
        free(t);
        return NULL;
    }
    t->size = size;
    return t;
}

void *tuple_get(Tuple *t, size_t index) {
    if (t == NULL || index >= t->size) {
        return NULL;
    }
    return t->items[index];
}

int tuple_set(Tuple *t, size_t index, void *item) {
    if (t == NULL || index >= t->size) {
        return -1;
    }
    t->items[index] = item;
    return 0;
}

void tuple_destroy(Tuple *t) {
    if (t != NULL) {
        free(t->items);
        free(t);
    }
}

int main(void) {
    Tuple *t = tuple_create(3);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    int a = 10;
    char *b = "hello";
    double c = 3.14;

    if (tuple_set(t, 0, &a) != 0 ||
        tuple_set(t, 1, b) != 0 ||
        tuple_set(t, 2, &c) != 0) {
        fprintf(stderr, "Failed to set tuple items\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }

    const int *item0 = tuple_get(t, 0);
    char *item1 = tuple_get(t, 1);
    const double *item2 = tuple_get(t, 2);

    if (item0 != NULL && item1 != NULL && item2 != NULL) {
        printf("Item 0: %d\n", *item0);
        printf("Item 1: %s\n", item1);
        printf("Item 2: %f\n", *item2);
    }

    const void *invalid = tuple_get(t, 5);
    if (invalid == NULL) {
        printf("Index 5 is out of bounds\n");
    }

    tuple_destroy(t);
    return EXIT_SUCCESS;
}