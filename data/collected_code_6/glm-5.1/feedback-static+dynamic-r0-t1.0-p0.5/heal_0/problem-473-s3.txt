#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int count;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int tuple_equal(Tuple t1, Tuple t2) {
    if (t1.count != t2.count) return 0;
    for (int i = 0; i < t1.count; i++) {
        if (t1.elements[i] != t2.elements[i]) return 0;
    }
    return 1;
}

TupleList find_tuple_intersection(TupleList list) {
    TupleList result;
    result.tuples = NULL;
    result.count = 0;

    if (list.count == 0) return result;

    for (int i = 0; i < list.count; i++) {
        if (list.tuples[i].count > 0) {
            qsort(list.tuples[i].elements, list.tuples[i].count, sizeof(int), compare_ints);
        }
    }

    int *is_unique = (int *)malloc(list.count * sizeof(int));
    if (!is_unique) return result;

    for (int i = 0; i < list.count; i++) {
        is_unique[i] = 1;
    }

    for (int i = 0; i < list.count; i++) {
        if (!is_unique[i]) continue;
        for (int j = i + 1; j < list.count; j++) {
            if (!is_unique[j]) continue;
            if (tuple_equal(list.tuples[i], list.tuples[j])) {
                is_unique[j] = 0;
            }
        }
    }

    int unique_count = 0;
    for (int i = 0; i < list.count; i++) {
        if (is_unique[i]) unique_count++;
    }

    if (unique_count > 0) {
        result.tuples = (Tuple *)malloc(unique_count * sizeof(Tuple));
        if (!result.tuples) {
            free(is_unique);
            result.count = 0;
            return result;
        }
        result.count = unique_count;

        int res_idx = 0;
        for (int i = 0; i < list.count; i++) {
            if (is_unique[i]) {
                result.tuples[res_idx].count = list.tuples[i].count;
                result.tuples[res_idx].elements = (int *)malloc(list.tuples[i].count * sizeof(int));
                if (!result.tuples[res_idx].elements) {
                    for (int k = 0; k < res_idx; k++) {
                        free(result.tuples[k].elements);
                    }
                    free(result.tuples);
                    free(is_unique);
                    result.tuples = NULL;
                    result.count = 0;
                    return result;
                }
                memcpy(result.tuples[res_idx].elements, list.tuples[i].elements, list.tuples[i].count * sizeof(int));
                res_idx++;
            }
        }
    }

    free(is_unique);
    return result;
}

void free_tuple_list(TupleList list) {
    for (int i = 0; i < list.count; i++) {
        free(list.tuples[i].elements);
    }
    free(list.tuples);
}

int main() {
    int e1[] = {3, 1, 2};
    int e2[] = {1, 2, 3};
    int e3[] = {4, 5};
    int e4[] = {5, 4};
    int e5[] = {1, 2, 3};

    Tuple tuples[] = {
        {e1, 3},
        {e2, 3},
        {e3, 2},
        {e4, 2},
        {e5, 3}
    };

    TupleList list = {tuples, 5};
    TupleList intersection = find_tuple_intersection(list);

    for (int i = 0; i < intersection.count; i++) {
        printf("(");
        for (int j = 0; j < intersection.tuples[i].count; j++) {
            printf("%d", intersection.tuples[i].elements[j]);
            if (j < intersection.tuples[i].count - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_tuple_list(intersection);

    return 0;
}