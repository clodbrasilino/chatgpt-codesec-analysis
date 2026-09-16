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

Tuple elementwise_and(Tuple t1, Tuple t2) {
    if (t1.size != t2.size) {
        exit(EXIT_FAILURE);
    }
    Tuple result = create_tuple(t1.size);
    for (size_t i = 0; i < t1.size; i++) {
        result.elements[i] = t1.elements[i] & t2.elements[i];
    }
    return result;
}

int main(void) {
    Tuple t1 = create_tuple(3);
    Tuple t2 = create_tuple(3);

    t1.elements[0] = 0x0F;
    t1.elements[1] = 0xF0;
    t1.elements[2] = 0xFF;

    t2.elements[0] = 0x0A;
    t2.elements[1] = 0x0F;
    t2.elements[2] = 0x00;

    Tuple res = elementwise_and(t1, t2);

    for (size_t i = 0; i < res.size; i++) {
        printf("%X ", res.elements[i]);
    }
    printf("\n");

    free_tuple(&t1);
    free_tuple(&t2);
    free_tuple(&res);

    return 0;
}