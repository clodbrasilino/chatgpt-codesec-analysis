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

static int tuple_equals(const Tuple *a, const Tuple *b) {
    if (a->size != b->size) return 0;
    for (int i = 0; i < a->size; i++) {
        if (a->elements[i] != b->elements[i]) return 0;
    }
    return 1;
}

static void assign_frequencies(TupleList *list) {
    if (list == NULL || list->tuples == NULL || list->count <= 0) return;

    for (int i = 0; i < list->count; i++) {
        list->tuples[i].frequency = 1;
        for (int j = 0; j < list->count; j++) {
            if (i != j && tuple_equals(&list->tuples[i], &list->tuples[j])) {
                list->tuples[i].frequency++;
            }
        }
    }

    for (int i = 0; i < list->count; i++) {
        for (int j = i + 1; j < list->count; j++) {
            if (tuple_equals(&list->tuples[i], &list->tuples[j])) {
                list->tuples[j].frequency = list->tuples[i].frequency;
            }
        }
    }
}

static TupleList *create_tuple_list(int count) {
    if (count <= 0) return NULL;

    TupleList *list = (TupleList *)malloc(sizeof(TupleList));
    if (list == NULL) return NULL;

    list->tuples = (Tuple *)calloc((size_t)count, sizeof(Tuple));
    if (list->tuples == NULL) {
        free(list);
        return NULL;
    }

    list->count = count;
    return list;
}

static void free_tuple_list(TupleList *list) {
    if (list == NULL) return;

    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
        list->tuples[i].elements = NULL;
    }
    free(list->tuples);
    list->tuples = NULL;
    free(list);
}

static int set_tuple_elements(Tuple *tuple, const int *source, int size) {
    if (tuple == NULL || source == NULL || size <= 0) return -1;

    tuple->elements = (int *)malloc((size_t)size * sizeof(int));
    if (tuple->elements == NULL) return -1;

    tuple->size = size;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->elements, source, (size_t)size * sizeof(int));
    return 0;
}

int main(void) {
    TupleList *list = create_tuple_list(5);
    if (list == NULL) return 1;

    /* Possible weaknesses found:
     *  Variable 't1' can be declared as const array [constVariable]
     */
    int t1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 't2' can be declared as const array [constVariable]
     */
    int t2[] = {4, 5};
    /* Possible weaknesses found:
     *  Variable 't3' can be declared as const array [constVariable]
     */
    int t3[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 't4' can be declared as const array [constVariable]
     */
    int t4[] = {6};
    /* Possible weaknesses found:
     *  Variable 't5' can be declared as const array [constVariable]
     */
    int t5[] = {4, 5};

    if (set_tuple_elements(&list->tuples[0], t1, 3) != 0) {
        free_tuple_list(list);
        return 1;
    }
    if (set_tuple_elements(&list->tuples[1], t2, 2) != 0) {
        free_tuple_list(list);
        return 1;
    }
    if (set_tuple_elements(&list->tuples[2], t3, 3) != 0) {
        free_tuple_list(list);
        return 1;
    }
    if (set_tuple_elements(&list->tuples[3], t4, 1) != 0) {
        free_tuple_list(list);
        return 1;
    }
    if (set_tuple_elements(&list->tuples[4], t5, 2) != 0) {
        free_tuple_list(list);
        return 1;
    }

    assign_frequencies(list);

    for (int i = 0; i < list->count; i++) {
        printf("Tuple %d: (", i);
        for (int j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) printf(", ");
        }
        printf(") - Frequency: %d\n", list->tuples[i].frequency);
    }

    free_tuple_list(list);
    return 0;
}