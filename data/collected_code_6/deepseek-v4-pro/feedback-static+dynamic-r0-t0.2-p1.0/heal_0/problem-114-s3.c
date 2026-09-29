#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
    int frequency;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int tuple_equals(const Tuple *a, const Tuple *b) {
    if (a->size != b->size) return 0;
    for (int i = 0; i < a->size; i++) {
        if (a->elements[i] != b->elements[i]) return 0;
    }
    return 1;
}

void assign_frequencies(TupleList *list) {
    if (list == NULL || list->tuples == NULL || list->count <= 0) return;

    for (int i = 0; i < list->count; i++) {
        list->tuples[i].frequency = 0;
    }

    for (int i = 0; i < list->count; i++) {
        if (list->tuples[i].frequency == 0) {
            int count = 1;
            for (int j = i + 1; j < list->count; j++) {
                if (tuple_equals(&list->tuples[i], &list->tuples[j])) {
                    count++;
                }
            }
            for (int j = i; j < list->count; j++) {
                if (tuple_equals(&list->tuples[i], &list->tuples[j])) {
                    list->tuples[j].frequency = count;
                }
            }
        }
    }
}

Tuple create_tuple(int *elements, int size) {
    Tuple t;
    t.size = size;
    t.frequency = 0;
    t.elements = (int *)malloc(size * sizeof(int));
    if (t.elements != NULL) {
        memcpy(t.elements, elements, size * sizeof(int));
    }
    return t;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) return;
    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

int main(void) {
    TupleList list;
    list.count = 5;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    if (list.tuples == NULL) return 1;

    int e1[] = {1, 2, 3};
    int e2[] = {4, 5};
    int e3[] = {1, 2, 3};
    int e4[] = {6};
    int e5[] = {4, 5};

    list.tuples[0] = create_tuple(e1, 3);
    list.tuples[1] = create_tuple(e2, 2);
    list.tuples[2] = create_tuple(e3, 3);
    list.tuples[3] = create_tuple(e4, 1);
    list.tuples[4] = create_tuple(e5, 2);

    assign_frequencies(&list);

    for (int i = 0; i < list.count; i++) {
        printf("Tuple %d: (", i);
        for (int j = 0; j < list.tuples[i].size; j++) {
            printf("%d", list.tuples[i].elements[j]);
            if (j < list.tuples[i].size - 1) printf(", ");
        }
        printf(") - frequency: %d\n", list.tuples[i].frequency);
    }

    free_tuple_list(&list);
    return 0;
}