#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

typedef struct {
    void **items;
    int *types;
    size_t size;
} Tuple;

Tuple *tuple_create(size_t size) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->items = (void **)malloc(size * sizeof(void *));
    if (t->items == NULL) {
        free(t);
        return NULL;
    }
    t->types = (int *)malloc(size * sizeof(int));
    if (t->types == NULL) {
        free(t->items);
        free(t);
        return NULL;
    }
    t->size = size;
    return t;
}

void tuple_add(Tuple *t, size_t index, void *item, int type) {
    if (t != NULL && index < t->size) {
        t->items[index] = item;
        t->types[index] = type;
    }
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->items);
        free(t->types);
        free(t);
    }
}

#define TUPLE_INT 1
#define TUPLE_FLOAT 2
#define TUPLE_CHAR 3

bool check_homogeneous(Tuple *t) {
    if (t == NULL || t->size == 0) {
        return true;
    }
    int first_type = t->types[0];
    for (size_t i = 1; i < t->size; i++) {
        if (t->types[i] != first_type) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Tuple *t1 = tuple_create(3);
    if (t1 == NULL) {
        return EXIT_FAILURE;
    }
    int a = 1, b = 2, c = 3;
    tuple_add(t1, 0, &a, TUPLE_INT);
    tuple_add(t1, 1, &b, TUPLE_INT);
    tuple_add(t1, 2, &c, TUPLE_INT);
    printf("%s\n", check_homogeneous(t1) ? "true" : "false");
    tuple_free(t1);

    Tuple *t2 = tuple_create(3);
    if (t2 == NULL) {
        return EXIT_FAILURE;
    }
    float x = 1.5f;
    tuple_add(t2, 0, &a, TUPLE_INT);
    tuple_add(t2, 1, &x, TUPLE_FLOAT);
    tuple_add(t2, 2, &c, TUPLE_INT);
    printf("%s\n", check_homogeneous(t2) ? "true" : "false");
    tuple_free(t2);

    return EXIT_SUCCESS;
}