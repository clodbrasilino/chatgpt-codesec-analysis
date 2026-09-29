#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
    int frequency;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

static int tuple_equals(const Tuple *a, const Tuple *b) {
    if (a->size != b->size) return 0;
    for (size_t i = 0; i < a->size; i++) {
        if (a->elements[i] != b->elements[i]) return 0;
    }
    return 1;
}

static void assign_frequencies(TupleList *list) {
    if (list == NULL || list->tuples == NULL || list->count == 0) return;

    for (size_t i = 0; i < list->count; i++) {
        list->tuples[i].frequency = 0;
        for (size_t j = 0; j < list->count; j++) {
            if (tuple_equals(&list->tuples[i], &list->tuples[j])) {
                list->tuples[i].frequency++;
            }
        }
    }
}

static TupleList *create_tuple_list(size_t count) {
    if (count == 0) return NULL;

    TupleList *list = (TupleList *)malloc(sizeof(TupleList));
    if (list == NULL) return NULL;

    list->tuples = (Tuple *)calloc(count, sizeof(Tuple));
    if (list->tuples == NULL) {
        free(list);
        return NULL;
    }

    list->count = count;
    return list;
}

static void free_tuple_list(TupleList *list) {
    if (list == NULL) return;

    for (size_t i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
        list->tuples[i].elements = NULL;
    }
    free(list->tuples);
    list->tuples = NULL;
    free(list);
}

static int set_tuple_elements(Tuple *tuple, const int *source, size_t size) {
    if (tuple == NULL || source == NULL || size == 0) return -1;

    if (size > (SIZE_MAX / sizeof(int))) return -1;

    size_t total_size = size * sizeof(int);
    tuple->elements = (int *)malloc(total_size);
    if (tuple->elements == NULL) return -1;

    tuple->size = size;
    memcpy(tuple->elements, source, total_size);
    return 0;
}

int main(void) {
    TupleList *list = create_tuple_list(5);
    if (list == NULL) return 1;

    const int t1[] = {1, 2, 3};
    const int t2[] = {4, 5};
    const int t3[] = {1, 2, 3};
    const int t4[] = {6};
    const int t5[] = {4, 5};

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

    for (size_t i = 0; i < list->count; i++) {
        printf("Tuple %zu: (", i);
        for (size_t j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) printf(", ");
        }
        printf(") - Frequency: %d\n", list->tuples[i].frequency);
    }

    free_tuple_list(list);
    return 0;
}