#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type; 
    union {
        int i;
        float f;
        char c;
    } value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    int size;
    int capacity;
} Tuple;

void init_tuple(Tuple *t, int capacity) {
    t->elements = (TupleElement *)malloc(capacity * sizeof(TupleElement));
    t->size = 0;
    t->capacity = capacity;
}

void free_tuple(Tuple *t) {
    free(t->elements);
    t->elements = NULL;
    t->size = 0;
    t->capacity = 0;
}

int add_element(Tuple *t, int type, int i, float f, char c) {
    if (t->size >= t->capacity) return -1;
    t->elements[t->size].type = type;
    switch (type) {
        case 0: t->elements[t->size].value.i = i; break;
        case 1: t->elements[t->size].value.f = f; break;
        case 2: t->elements[t->size].value.c = c; break;
    }
    t->size++;
    return 0;
}

void remove_elements_by_type(Tuple *t, int type) {
    int read = 0;
    int write = 0;
    while (read < t->size) {
        if (t->elements[read].type != type) {
            t->elements[write] = t->elements[read];
            write++;
        }
        read++;
    }
    t->size = write;
}

void print_tuple(const Tuple *t) {
    for (int i = 0; i < t->size; ++i) {
        switch (t->elements[i].type) {
            case 0: printf("%d ", t->elements[i].value.i); break;
            case 1: printf("%f ", t->elements[i].value.f); break;
            case 2: printf("%c ", t->elements[i].value.c); break;
        }
    }
    printf("\n");
}

int main() {
    Tuple t;
    init_tuple(&t, 10);

    add_element(&t, 0, 1, 0.0, 0);
    add_element(&t, 1, 0, 2.5, 0);
    add_element(&t, 2, 0, 0.0, 'a');
    add_element(&t, 0, 2, 0.0, 0);
    add_element(&t, 1, 0, 3.5, 0);

    printf("Original tuple: ");
    print_tuple(&t);

    remove_elements_by_type(&t, 1);

    printf("Modified tuple: ");
    print_tuple(&t);

    free_tuple(&t);
    return 0;
}