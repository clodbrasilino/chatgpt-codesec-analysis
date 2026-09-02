#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int size;
} TupleList;

int cumulative_sum(TupleList *list) {
    int sum = 0;
    for (int i = 0; i < list->size; i++) {
        Tuple *tuple = &list->tuples[i];
        for (int j = 0; j < tuple->size; j++) {
            sum += tuple->values[j];
        }
    }
    return sum;
}

Tuple *create_tuple(const int *values, int size) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    tuple->values = (int *)malloc(sizeof(int) * size);
    if (!tuple->values) {
        free(tuple);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        tuple->values[i] = values[i];
    }
    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple) {
        free(tuple->values);
        free(tuple);
    }
}

void free_tuple_list(TupleList *list) {
    if (list) {
        for (int i = 0; i < list->size; i++) {
            free(list->tuples[i].values);
        }
        free(list->tuples);
    }
}

int main(void) {
    const int values1[] = {1, 2, 3};
    const int values2[] = {4, 5};
    const int values3[] = {6, 7, 8, 9};

    Tuple *t1 = create_tuple(values1, 3);
    Tuple *t2 = create_tuple(values2, 2);
    Tuple *t3 = create_tuple(values3, 4);

    if (!t1 || !t2 || !t3) {
        free_tuple(t1);
        free_tuple(t2);
        free_tuple(t3);
        return 1;
    }

    TupleList list;
    list.size = 3;
    list.tuples = (Tuple *)malloc(sizeof(Tuple) * list.size);
    if (!list.tuples) {
        free_tuple(t1);
        free_tuple(t2);
        free_tuple(t3);
        return 1;
    }

    list.tuples[0] = *t1;
    list.tuples[1] = *t2;
    list.tuples[2] = *t3;
    free(t1);
    free(t2);
    free(t3);

    int result = cumulative_sum(&list);
    printf("%d\n", result);

    free_tuple_list(&list);
    return 0;
}