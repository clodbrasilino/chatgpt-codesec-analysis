#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int count;
} Set;

typedef struct {
    int a;
    int b;
} Tuple;

int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

Tuple *set_to_ordered_tuples(const Set *set, int *tuple_count) {
    if (set == NULL || tuple_count == NULL) {
        return NULL;
    }
    if (set->count < 0 || set->elements == NULL) {
        *tuple_count = 0;
        return NULL;
    }

    int *sorted = (int *)malloc(set->count * sizeof(int));
    if (sorted == NULL) {
        *tuple_count = 0;
        return NULL;
    }

    for (int i = 0; i < set->count; ++i) {
        sorted[i] = set->elements[i];
    }

    qsort(sorted, set->count, sizeof(int), compare_ints);

    int unique_count = 0;
    for (int i = 0; i < set->count; ++i) {
        if (i == 0 || sorted[i] != sorted[i - 1]) {
            sorted[unique_count++] = sorted[i];
        }
    }

    if (unique_count < 2) {
        free(sorted);
        *tuple_count = 0;
        return NULL;
    }

    int t_count = unique_count * (unique_count - 1) / 2;
    Tuple *tuples = (Tuple *)malloc(t_count * sizeof(Tuple));
    if (tuples == NULL) {
        free(sorted);
        *tuple_count = 0;
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < unique_count; ++i) {
        for (int j = i + 1; j < unique_count; ++j) {
            tuples[idx].a = sorted[i];
            tuples[idx].b = sorted[j];
            idx++;
        }
    }

    free(sorted);
    *tuple_count = t_count;
    return tuples;
}

int main(void) {
    int data[] = {4, 2, 5, 2, 1, 3};
    Set set = {data, 6};

    int tuple_count = 0;
    Tuple *tuples = set_to_ordered_tuples(&set, &tuple_count);

    if (tuples != NULL) {
        for (int i = 0; i < tuple_count; ++i) {
            printf("(%d, %d)\n", tuples[i].a, tuples[i].b);
        }
        free(tuples);
    }

    return 0;
}