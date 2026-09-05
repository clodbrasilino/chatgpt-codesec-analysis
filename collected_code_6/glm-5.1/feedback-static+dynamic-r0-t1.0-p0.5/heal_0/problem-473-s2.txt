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
        int *sorted = malloc(list.tuples[i].count * sizeof(int));
        if (!sorted) {
            for (int k = 0; k < result.count; k++) free(result.tuples[k].elements);
            free(result.tuples);
            result.tuples = NULL;
            result.count = 0;
            return result;
        }
        memcpy(sorted, list.tuples[i].elements, list.tuples[i].count * sizeof(int));
        qsort(sorted, list.tuples[i].count, sizeof(int), compare_ints);

        int is_unique = 1;
        for (int j = 0; j < result.count; j++) {
            Tuple temp;
            temp.elements = sorted;
            temp.count = list.tuples[i].count;
            if (tuple_equal(result.tuples[j], temp)) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique) {
            Tuple *new_tuples = realloc(result.tuples, (result.count + 1) * sizeof(Tuple));
            if (!new_tuples) {
                free(sorted);
                for (int k = 0; k < result.count; k++) free(result.tuples[k].elements);
                free(result.tuples);
                result.tuples = NULL;
                result.count = 0;
                return result;
            }
            result.tuples = new_tuples;
            result.tuples[result.count].elements = sorted;
            result.tuples[result.count].count = list.tuples[i].count;
            result.count++;
        } else {
            free(sorted);
        }
    }

    return result;
}

void free_tuple_list(TupleList list) {
    for (int i = 0; i < list.count; i++) {
        free(list.tuples[i].elements);
    }
    free(list.tuples);
}

int main() {
    int a1[] = {3, 1, 2};
    int a2[] = {1, 2, 3};
    int a3[] = {4, 5};
    int a4[] = {5, 4};
    int a5[] = {1, 2, 3};

    Tuple t1 = {a1, 3};
    Tuple t2 = {a2, 3};
    Tuple t3 = {a3, 2};
    Tuple t4 = {a4, 2};
    Tuple t5 = {a5, 3};

    Tuple tuples_arr[] = {t1, t2, t3, t4, t5};
    TupleList list = {tuples_arr, 5};

    TupleList intersection = find_tuple_intersection(list);

    for (int i = 0; i < intersection.count; i++) {
        printf("(");
        for (int j = 0; j < intersection.tuples[i].count; j++) {
            printf("%d", intersection.tuples[i].elements[j]);
            if (j < intersection.tuples[i].count - 1) printf(", ");
        }
        printf(")\n");
    }

    free_tuple_list(intersection);

    return 0;
}