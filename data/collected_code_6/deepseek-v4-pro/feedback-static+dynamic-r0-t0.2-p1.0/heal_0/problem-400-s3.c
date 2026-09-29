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
    int capacity;
} TupleList;

static int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

static int tuples_equal(const Tuple *a, const Tuple *b) {
    if (a->size != b->size) return 0;
    for (int i = 0; i < a->size; i++) {
        if (a->elements[i] != b->elements[i]) return 0;
    }
    return 1;
}

static void sort_tuple(Tuple *t) {
    qsort(t->elements, t->size, sizeof(int), compare_ints);
}

static void add_tuple(TupleList *list, Tuple *t) {
    for (int i = 0; i < list->count; i++) {
        if (tuples_equal(&list->tuples[i], t)) {
            list->tuples[i].frequency++;
            free(t->elements);
            return;
        }
    }
    if (list->count == list->capacity) {
        list->capacity = list->capacity == 0 ? 8 : list->capacity * 2;
        list->tuples = realloc(list->tuples, list->capacity * sizeof(Tuple));
        if (!list->tuples) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    list->tuples[list->count] = *t;
    list->tuples[list->count].frequency = 1;
    list->count++;
}

static void free_tuple_list(TupleList *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
    list->capacity = 0;
}

void extract_tuple_frequencies(int **tuples, int *tuple_sizes, int tuple_count, TupleList *result) {
    result->tuples = NULL;
    result->count = 0;
    result->capacity = 0;

    for (int i = 0; i < tuple_count; i++) {
        Tuple t;
        t.size = tuple_sizes[i];
        t.elements = malloc(t.size * sizeof(int));
        if (!t.elements) {
            fprintf(stderr, "Memory allocation failed\n");
            free_tuple_list(result);
            exit(EXIT_FAILURE);
        }
        memcpy(t.elements, tuples[i], t.size * sizeof(int));
        sort_tuple(&t);
        add_tuple(result, &t);
    }
}

int main(void) {
    int t1[] = {3, 1, 2};
    int t2[] = {2, 1, 3};
    int t3[] = {4, 5};
    int t4[] = {5, 4};
    int t5[] = {1, 2, 3};
    int t6[] = {7, 8};

    int *tuples[] = {t1, t2, t3, t4, t5, t6};
    int sizes[] = {3, 3, 2, 2, 3, 2};
    int count = 6;

    TupleList result;
    extract_tuple_frequencies(tuples, sizes, count, &result);

    for (int i = 0; i < result.count; i++) {
        printf("Tuple (");
        for (int j = 0; j < result.tuples[i].size; j++) {
            printf("%d", result.tuples[i].elements[j]);
            if (j < result.tuples[i].size - 1) printf(", ");
        }
        printf(") : %d\n", result.tuples[i].frequency);
    }

    free_tuple_list(&result);
    return 0;
}