#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple* create_tuple(size_t size) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (!t) {
        return NULL;
    }
    t->size = size;
    t->elements = (int*)malloc(size * sizeof(int));
    if (!t->elements) {
        free(t);
        return NULL;
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (t) {
        free(t->elements);
        free(t);
    }
}

Tuple* elementwise_and(const Tuple *t1, const Tuple *t2) {
    if (!t1 || !t2 || t1->size != t2->size) {
        return NULL;
    }

    Tuple *result = create_tuple(t1->size);
    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < t1->size; ++i) {
        result->elements[i] = t1->elements[i] & t2->elements[i];
    }

    return result;
}

int main() {
    size_t size = 4;
    Tuple *t1 = create_tuple(size);
    Tuple *t2 = create_tuple(size);

    if (!t1 || !t2) {
        free_tuple(t1);
        free_tuple(t2);
        return 1;
    }

    t1->elements[0] = 10; t1->elements[1] = 4; t1->elements[2] = 6; t1->elements[3] = 9;
    t2->elements[0] = 5;  t2->elements[1] = 2; t2->elements[2] = 3; t2->elements[3] = 3;

    Tuple *result = elementwise_and(t1, t2);

    if (result) {
        for (size_t i = 0; i < result->size; ++i) {
            printf("%d ", result->elements[i]);
        }
        printf("\n");
    }

    free_tuple(t1);
    free_tuple(t2);
    free_tuple(result);

    return 0;
}