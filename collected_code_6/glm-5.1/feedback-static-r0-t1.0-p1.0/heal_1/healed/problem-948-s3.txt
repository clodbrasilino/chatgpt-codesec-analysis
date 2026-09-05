#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct {
    void **items;
    size_t size;
} Tuple;

Tuple *tuple_create(size_t size, ...) {
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) return NULL;

    t->size = size;
    t->items = malloc(size * sizeof(void *));
    if (t->items == NULL) {
        free(t);
        return NULL;
    }

    va_list args;
    va_start(args, size);
    for (size_t i = 0; i < size; i++) {
        t->items[i] = va_arg(args, void *);
    }
    va_end(args);

    return t;
}

void tuple_destroy(Tuple *t) {
    if (t != NULL) {
        free(t->items);
        free(t);
    }
}

int tuple_get(Tuple *t, size_t index, void **out_item) {
    if (t == NULL || out_item == NULL) return -1;
    if (index >= t->size) return -2;
    *out_item = t->items[index];
    return 0;
}

int main(void) {
    int a = 10;
    double b = 3.14;
    char c = 'X';

    Tuple *t = tuple_create(3, &a, &b, &c);
    if (t == NULL) return 1;

    void *item = NULL;

    if (tuple_get(t, 0, &item) == 0) {
        const int *int_ptr = (const int *)item;
        printf("Item 0: %d\n", *int_ptr);
    }

    if (tuple_get(t, 1, &item) == 0) {
        const double *dbl_ptr = (const double *)item;
        printf("Item 1: %f\n", *dbl_ptr);
    }

    if (tuple_get(t, 2, &item) == 0) {
        const char *char_ptr = (const char *)item;
        printf("Item 2: %c\n", *char_ptr);
    }

    if (tuple_get(t, 3, &item) == 0) {
        printf("Item 3: %p\n", item);
    } else {
        printf("Item 3: Out of bounds\n");
    }

    tuple_destroy(t);
    return 0;
}