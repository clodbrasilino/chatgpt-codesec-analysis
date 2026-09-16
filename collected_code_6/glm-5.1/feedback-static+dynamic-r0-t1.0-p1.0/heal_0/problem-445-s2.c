#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple create_tuple(size_t size) {
    Tuple t;
    t.size = size;
    t.elements = (int *)malloc(size * sizeof(int));
    if (t.elements == NULL) {
        exit(EXIT_FAILURE);
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL && t->elements != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

Tuple multiply_tuples(const Tuple t1, const Tuple t2) {
    if (t1.size != t2.size) {
        Tuple empty = {NULL, 0};
        return empty;
    }

    Tuple result = create_tuple(t1.size);

    for (size_t i = 0; i < result.size; i++) {
        result.elements[i] = t1.elements[i] * t2.elements[i];
    }

    return result;
}

int main(void) {
    size_t size = 5;
    Tuple t1 = create_tuple(size);
    Tuple t2 = create_tuple(size);

    int vals1[] = {1, 2, 3, 4, 5};
    int vals2[] = {6, 7, 8, 9, 10};

    for (size_t i = 0; i < size; i++) {
        t1.elements[i] = vals1[i];
        t2.elements[i] = vals2[i];
    }

    Tuple result = multiply_tuples(t1, t2);

    if (result.elements != NULL) {
        for (size_t i = 0; i < result.size; i++) {
            printf("%d ", result.elements[i]);
        }
        printf("\n");
    }

    free_tuple(&t1);
    free_tuple(&t2);
    free_tuple(&result);

    return 0;
}